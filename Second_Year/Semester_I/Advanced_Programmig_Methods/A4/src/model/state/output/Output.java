package model.state.output;

import model.ADTs.list.IList;
import model.ADTs.list.MyList;

import java.util.List;

public class Output implements IOutput {
    IList<String> data;

    public Output() {
        this.data = new MyList<>();
    }

    @Override
    public List<String> getAll() {
        return this.data.getAll();
    }

    @Override
    public void add(String string) {
        this.data.add(string);
    }

    @Override
    public void setOutput(String string) {
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
