import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;

public class ModeloRegresion {

    private double intercept;
    private Map<String, Double> coeficientes;
    private double limite;


    public void ModeloRegresion(String path) {
        try{
            BufferedReader archivo= new BufferedReader(new FileReader(path));

            String linea;
            linea=archivo.readLine();

            String line;
            String total="";
            while ((line = archivo.readLine()) != null) {
               total = total.concat(line);
            }
            String search = "\"intercept\":";
            int index = total.indexOf(search) + search.length();
            this.intercept = Double.parseDouble(total.substring(index, total.indexOf(",", index)).trim());

            coeficientes= new HashMap<>();
            String start = "\"coefficients\": {";
            int startIndex = total.indexOf(start) + start.length();
            int endIndex = total.indexOf("}", startIndex);

            String body = total.substring(startIndex, endIndex).trim();
            String[] entries = body.split(",");

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

    public double Prediccion(Aplicante aplicante) {

        return intercept+
                (coeficientes.get("GRE Score")* aplicante.getGreScore())+
                (coeficientes.get("TOEFL Score")* aplicante.getToeflScore())+
                (coeficientes.get("TOEFL Score")* aplicante.getUniversityRating())+
                (coeficientes.get("University Rating")* aplicante.getSop())+
                (coeficientes.get("SOP")* aplicante.getLor())+
                (coeficientes.get("LOR")* aplicante.getCGPA())+
                (coeficientes.get("CGPA")* aplicante.getResearch());

    }


    public boolean Admitido(Aplicante aplicante, double limite) {
        return Prediccion(aplicante)>=limite;
    }


}
