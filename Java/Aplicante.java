public class Aplicante {

    private int GreScore;
    private int ToeflScore;
    private int UniversityRating;
    private double Sop;
    private double Lor;
    private double CGPA;
    private int Research;


    public Aplicante(int GreScore, int ToeflScore, int UniversityRating, float Sop, float Lor, float CGPA, int Research) {
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
    public int getGreScore() {
        return GreScore;
    }
    public int getToeflScore() {
        return ToeflScore;
    }
    public int getUniversityRating() {
        return UniversityRating;
    }
    public float getSop() {
        return Sop;
    }
    public float getLor() {
        return Lor;
    }
    public float getCGPA() {
        return CGPA;
    }
    public int getResearch() {
        return Research;
    }

}
