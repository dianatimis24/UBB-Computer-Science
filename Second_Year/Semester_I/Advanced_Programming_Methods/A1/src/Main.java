// 7. Se da o colectie de mai multe obiecte, avand forme de cuburi, sfere si cilindri.
// Sa se afiseze obiectele avand volumul mai mare decat 25cm^3.

import controller.Controller;
import model.*;
import repository.*;
import view.View;

void main() {
    IRepository repository = new Repository(100);
    Controller controller = new Controller(repository);
    View view = new View(controller);
    view.run();
}
