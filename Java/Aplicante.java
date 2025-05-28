public class Aplicante {

    //Atributos del aplicante
    private final String nombre;
    private int GreScore;
    private int ToeflScore;
    private int UniversityRating;
    private double Sop;
    private double Lor;
    private double CGPA;
    private int Research;

    //Constructor por parametros
    public Aplicante(String nombre,int GreScore, int ToeflScore, int UniversityRating, double Sop, double Lor, double CGPA, int Research) {
        this.nombre=nombre;
        this.GreScore = GreScore;
        this.ToeflScore = ToeflScore;
        this.UniversityRating = UniversityRating;
        this.Sop = Sop;
        this.Lor = Lor;
        this.CGPA = CGPA;
        this.Research = Research;
    }


    //Setters
    public void setGreScore(int greScore) {
        GreScore = greScore;
    }
    public void setToeflScore(int toeflScore) {
        ToeflScore = toeflScore;
    }
    public void setUniversityRating(int universityRating) {
        UniversityRating = universityRating;
    }
    public void setSop(float Sop) {
        this.Sop = Sop;
    }
    public void setLor(float Lor) {
        this.Lor = Lor;
    }
    public void setCGPA(float CGPA) {
        this.CGPA = CGPA;
    }
    public void setResearch(int Research) {
        this.Research = Research;
    }

    //Getters
    public String getNombre() {
        return nombre;
    }
    public int getGreScore() {
        return GreScore;
    }
    public int getToeflScore() {
        return ToeflScore;
    }
    public int getUniversityRating() {
        return UniversityRating;
    }
    public double getSop() {
        return Sop;
    }
    public double getLor() {
        return Lor;
    }
    public double getCGPA() {
        return CGPA;
    }
    public int getResearch() {
        return Research;
    }

}
