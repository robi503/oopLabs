#include "UndoAction.h"

UndoAdd::UndoAdd(Repo* undoRepo, const Book addedBook) : UndoAction { undoRepo }, book { addedBook } {}

void UndoAdd::doUndo()
{
	int i = 0;
	Repo* r = getRepo();
	for (const Book& b : r->getAll()) {
		if (b == book) {
			r->remove(i);
		}
		i++;
	}
}

UndoDelete::UndoDelete(Repo* undoRepo, const Book deletedBook) : UndoAction{ undoRepo }, book{ deletedBook } {}

void UndoDelete::doUndo()
{
	Repo* r = getRepo();
	r->add(book);
}

UndoModify::UndoModify(Repo* undoRepo, const Book oldBook, const Book newBook) : UndoAction{ undoRepo },
	oldBook{ oldBook }, newBook { newBook } {}

void UndoModify::doUndo()
{
	int i = 0;
	Repo* r = getRepo();
	for (const Book& b : r->getAll()) {
		if (b == newBook) {
			r->remove(i);
			r->add(oldBook);
		}
		i++;
	}
}
