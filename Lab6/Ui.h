#pragma once
#include "BookService.h"

class Ui
{
private:
	BookService service;
	bool running = true;

public:
	Ui();
	void printMenu() const;
	void handleAdd();
	void handleModify();
	void handleDelete();
	void handleAddToCart();
	void handleEmptyCart();
	void handleGenerateCart();
	void handleExportCart();
	void printAllBooks() const;
	void handleGetOne() const;
	void handleFilter() const;
	void handleSort() const;
	void addDummy();
	void handleUndo();
	void run();
};

