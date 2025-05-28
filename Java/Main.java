import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            FormularioAplicante frame = new FormularioAplicante(); //Se crea la interfaz grafica
            frame.setVisible(true);
        });
    }
}
