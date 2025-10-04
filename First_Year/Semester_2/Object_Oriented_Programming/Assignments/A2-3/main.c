#include <stdio.h>
#include <crtdbg.h>
#include "CountryRepository.h"
#include "CountryService.h"
#include "UI.h"
#include "TestAll.h"

int main() {
    testAll();

    int typeOfUndoRedo = 2;
    CountryRepository* repository = createCountryRepository();
    UndoRedoRepository* undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    CountryService* service = createCountryService(repository, undoRedoRepository, typeOfUndoRedo);
    UI* ui = createUI(service);
    startUI(ui);
    destroyUI(ui);

    _CrtDumpMemoryLeaks();
    return 0;
}