module src.toy_language_interpreter {
    requires javafx.controls;
    requires javafx.fxml;

    opens view.gui to javafx.fxml;
    opens model.value to javafx.base;
    opens model.type to javafx.base;
    opens model.state to javafx.base;

    exports src.toy_language_interpreter;
}