package model.state.output;

import model.ADTs.list.IList;
import model.ADTs.list.MyList;
import model.ADTs.list.MySynchronizedList;

import java.util.List;

public class Output implements IOutput {
    private final IList<String> data = new MySynchronizedList<>();

    @Override
    public synchronized List<String> getAll() {
        return this.data.getAll();
    }

    @Override
    public synchronized void add(String string) {
        this.data.add(string);
    }

    @Override
    public synchronized void setOutput(String string) {
        this.data.clear();
        this.data.add(string);
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("Output:\n");
        for (String element : this.data.getAll()) {
            answer.append(element).append("\n");
        }
        return answer.toString();
    }
}
