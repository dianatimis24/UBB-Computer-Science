package model.state.output;

import java.util.List;

public interface IOutput {
    List<String> getAll();
    void add(String string);
    void setOutput(String string);
    String toString();
}
