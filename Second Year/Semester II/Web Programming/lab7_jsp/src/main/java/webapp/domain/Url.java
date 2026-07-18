package webapp.domain;

public class Url {
    private int id;
    private String urlAddress;
    private String title;
    private int saves;

    public Url(int id, String urlAddress, String title) {
        this.id = id;
        this.urlAddress = urlAddress;
        this.title = title;
        this.saves = 0;
    }

    public Url(int id, String urlAddress, String title, int saves) {
        this.id = id;
        this.urlAddress = urlAddress;
        this.title = title;
        this.saves = saves;
    }

    public int getId() {
        return this.id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUrlAddress() {
        return this.urlAddress;
    }

    public void setUrlAddress(String urlAddress) {
        this.urlAddress = urlAddress;
    }

    public String getTitle() {
        return this.title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public int getSaves() {
        return this.saves;
    }

    public void setSaves(int saves) {
        this.saves = saves;
    }
}