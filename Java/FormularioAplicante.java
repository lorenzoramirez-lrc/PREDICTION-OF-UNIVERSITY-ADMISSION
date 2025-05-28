import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

//Clase que hereda de JFrame para la interfaz grafica
public class FormularioAplicante extends JFrame {
    //Componentes graficos
    private JTextField nombreField;
    private JTextField greField;
    private JTextField toeflField;
    private JTextField ratingField;
    private JTextField sopField;
    private JTextField lorField;
    private JTextField cgpaField;
    private JCheckBox researchCheck;
    private JLabel resultadoLabel;
    private JLabel imagenResultado;
    private JButton submitButton;
    private ModeloRegresion modelo;

    //Constuructor de la interfaz
    public FormularioAplicante() {

        //Configuracion ventana
        setTitle("Aplicación Universitaria");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Título
        JLabel titulo = new JLabel("Formulario de Aplicación a la Universidad", SwingConstants.CENTER);
        titulo.setFont(new Font("Arial", Font.BOLD, 18));
        add(titulo, BorderLayout.NORTH);

        // Panel del formulario con distribucion de botones
        JPanel formPanel = new JPanel(new GridLayout(8, 2, 10, 5));

        //Se inicializan los campos de texto
        nombreField = new JTextField();
        greField = new JTextField();
        toeflField = new JTextField();
        ratingField = new JTextField();
        sopField = new JTextField();
        lorField = new JTextField();
        cgpaField = new JTextField();
        researchCheck = new JCheckBox("¿Tiene experiencia en investigación?");

        //Etiquetas y paneles
        formPanel.add(new JLabel("Nombre:"));
        formPanel.add(nombreField);
        formPanel.add(new JLabel("GRE Score:"));
        formPanel.add(greField);
        formPanel.add(new JLabel("TOEFL Score:"));
        formPanel.add(toeflField);
        formPanel.add(new JLabel("University Rating:"));
        formPanel.add(ratingField);
        formPanel.add(new JLabel("SOP:"));
        formPanel.add(sopField);
        formPanel.add(new JLabel("LOR:"));
        formPanel.add(lorField);
        formPanel.add(new JLabel("CGPA:"));
        formPanel.add(cgpaField);
        formPanel.add(researchCheck);
        formPanel.add(new JLabel());

        add(formPanel, BorderLayout.CENTER);

        //Label que muestra el resultado
        resultadoLabel = new JLabel(" ", SwingConstants.CENTER);
        add(resultadoLabel, BorderLayout.SOUTH);
        resultadoLabel.setFont(new Font("Arial", Font.BOLD, 16));

        // Imagen del resultado
        imagenResultado = new JLabel("", SwingConstants.CENTER);
        add(imagenResultado, BorderLayout.CENTER);

        // Botón de envío
        submitButton = new JButton("Evaluar Aplicación");
        add(submitButton, BorderLayout.WEST);

        // Cargar modelo desde JSON
        modelo = new ModeloRegresion("data/modelo_parametros.json"); // Asegúrate de tener este archivo

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    //Se crea el objeto aplicante con los datos ingresados
                    Aplicante aplicante = new Aplicante(
                            nombreField.getText(),
                            Integer.parseInt(greField.getText()),
                            Integer.parseInt(toeflField.getText()),
                            Integer.parseInt(ratingField.getText()),
                            Double.parseDouble(sopField.getText()),
                            Double.parseDouble(lorField.getText()),
                            Double.parseDouble(cgpaField.getText()),
                            researchCheck.isSelected() ? 1 : 0
                    );

                    //Evaluar si fue admitido
                    boolean admitido = modelo.admitido(aplicante, 0.8); // ejemplo umbral

                    String mensaje;
                    String rutaImagen;

                    //Se configura el mensaje con base al resultado
                    if (admitido) {
                        mensaje = String.format(aplicante.getNombre() +" has sido admitido (puntaje: %.2f)",modelo.prediccion(aplicante));
                        rutaImagen = "data/admitido.png";
                        resultadoLabel.setForeground(new Color(0, 128, 0));
                    } else {
                        mensaje = String.format(aplicante.getNombre() +" no has sido admitido (puntaje: %.2f)", modelo.prediccion(aplicante));
                        rutaImagen = "data/no_admitido.png";
                        resultadoLabel.setForeground(Color.RED);
                    }

                    //Se muestra imagen y resultado
                    resultadoLabel.setText(mensaje);
                    imagenResultado.setIcon(new ImageIcon(rutaImagen));

                } catch (NumberFormatException ex) {
                    //Atrapa error en el formato de los campos
                    resultadoLabel.setText("Por favor, completa todos los campos correctamente (Solo se aceptan numeros)");
                }
            }
        });
    }


}
