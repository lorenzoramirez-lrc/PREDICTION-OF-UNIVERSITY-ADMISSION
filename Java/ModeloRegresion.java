import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;

public class ModeloRegresion {

    //Atributos del modelo de regresion
    private double intercept;
    private Map<String, Double> coeficientes;


    //Constructor del modelo
    public ModeloRegresion(String path) {
        try{
            //Apertura archivo JSON
            BufferedReader archivo= new BufferedReader(new FileReader(path));


            String linea;
            linea=archivo.readLine();


            String line;
            String total="";

            //Se lee todo el JSON en un string

            while ((line = archivo.readLine()) != null) {
               total = total.concat(line);
            }
            //Se busca en el string donde este el intercepto  y se encuentra el indice
            String search = "\"intercept\":";
            int index = total.indexOf(search) + search.length();
            //Se parsea el double desde el indice hasta la coma
            this.intercept = Double.parseDouble(total.substring(index, total.indexOf(",", index)).trim());

            coeficientes= new HashMap<>();
            //Se encuentran los coeficientes en el JSON
            String start = "\"coefficients\": {";
            int startIndex = total.indexOf(start) + start.length();
            int endIndex = total.indexOf("}", startIndex);

            //Se obtiene el string de los coeficientes y se quitan los espacios
            String body = total.substring(startIndex, endIndex).trim();
            //Se separa los coeficientes por las comsa
            String[] entries = body.split(",");

            //Para cada coeficiente se separa su nombre y su valor
            for (String entry : entries) {
                String[] parts = entry.split(":");
                String key = parts[0].trim().replace("\"", "");
                Double value = Double.parseDouble(parts[1].trim());
                coeficientes.put(key, value);
            }



        }catch(Exception e){
            e.printStackTrace();
        }



    }

    /*Con base en un aplicante se obtiene su resultado a travez de la
    regresion lineal utilizando los coeficientes del JSON
     */
    public double prediccion(Aplicante aplicante) {

        return intercept+
                (coeficientes.get("GRE Score")* aplicante.getGreScore())+
                (coeficientes.get("TOEFL Score")* aplicante.getToeflScore())+
                (coeficientes.get("University Rating")* aplicante.getUniversityRating())+
                (coeficientes.get("SOP")* aplicante.getSop())+
                (coeficientes.get("LOR")* aplicante.getLor())+
                (coeficientes.get("CGPA")* aplicante.getCGPA())+
                (coeficientes.get("Research")* aplicante.getResearch());

    }

    //Se regresa un booleano sabiendo si el aplicante fue admitido o no
    public boolean admitido(Aplicante aplicante) {
        return prediccion(aplicante)>=0.8;
    }


}
