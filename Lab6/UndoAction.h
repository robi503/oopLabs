#include "Repo.h"

class UndoAction
{
private:
	Repo* repo;
public:
	UndoAction(Repo* undoRepo) : repo(undoRepo) {};
	virtual void doUndo() {};
	virtual ~UndoAction() {};
	Repo* getRepo() const { return repo; }
};

class UndoAdd : public UndoAction
{
private:
	const Book book;
public:
	UndoAdd(Repo* undoRepo, const Book book);
	virtual void doUndo() override;
};

class UndoDelete : public UndoAction
{
private:
	const Book book;
public:
	UndoDelete(Repo* undoRepo, const Book book);
	virtual void doUndo() override;
};

class UndoModify : public UndoAction
{
private:
	const Book oldBook;
	const Book newBook;
public:
	UndoModify(Repo* undoRepo, const Book oldBook, const Book newBook);
	virtual void doUndo() override;
};
