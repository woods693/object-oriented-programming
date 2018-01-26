#include "stocksystem.h"
//Woody Chen Lin Chang
//301231083
//CMPT225
 
// default constructor;
// begin with a balance of $100,000.00
StockSystem::StockSystem()
{
	balance = 100000.00; //initial 100,000.00
}

 
// returns the balance member
double StockSystem::GetBalance()
{
	return balance;
}

    // Add a new SKU to the system. Do not allow insertion of duplicate sku
bool StockSystem::StockNewItem(StockItem item)
{
	return records.Insert(item); //calls upon insert function
}

    // Locate the item with key itemsku and update its description field.
    // Return false if itemsku is not found.
bool StockSystem::EditStockItemDescription(unsigned int itemsku, string desc)
{
	StockItem* temp = new StockItem(itemsku, "", 0); //new
	StockItem* found = records.Retrieve(*temp);
	delete temp; 
	if(found != NULL) //NULL means not in tree
	{
		found->SetDescription(desc); //call upon SetDescription func
		return true;
	}
	else
	{
		return false;
	}
}

    // Locate the item with key itemsku and update its description field.
    // Return false if itemsku is not found.
bool StockSystem::EditStockItemPrice(unsigned int itemsku, double retailprice)
{
	StockItem* temp = new StockItem(itemsku, "", 0);
	StockItem* found = records.Retrieve(*temp);
	delete temp;
	if(found != NULL)
	{
		found->SetPrice(retailprice);
		return true;
	}
	else
	{
		return false;
	}
}

    // Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
    // Return false if balance is not sufficient to make the purchase,
    //   or if SKU does not exist.
    // Otherwise, return true and increase the item's on-hand stock by quantity,
    //   and reduce balance by quantity*unitprice.
bool StockSystem::Restock(unsigned int itemsku, unsigned int quantity, double unitprice)
{
	StockItem* item = records.Retrieve(StockItem(itemsku,"",0));
	if(item == NULL)
	{
		return false;
	}

	if(quantity + item->GetStock() > 1000) //on-hand stock quantity of 1000.
	{
		quantity = 1000 - item->GetStock();
	}

	if(unitprice * quantity > balance)
	{
		return false; //balance insufficient
	}

	balance -= unitprice * quantity; //reduce balance by quantity*unitprice.
	item->SetStock(item->GetStock() + quantity); //increase onhand stock quantity

	return true;

}

    // Sell an item to a customer, if quantity of stock is available and SKU exists.
    // Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
    // If partial stock (less than quantity) available, sell the available stock and return true.
    // If no stock or sku does not exist, return false.
bool StockSystem::Sell(unsigned int itemsku, unsigned int quantity)
{
	StockItem* item = records.Retrieve(StockItem(itemsku,"",0));
	if(item == NULL || item->GetStock() == 0) //if quantity of stock is available and SKU exists.
	{
		return false;
	}

	if(quantity > item->GetStock())
	{
		balance += item->GetStock() * item->GetPrice(); //If partial stock (less than quantity) available, sell the available stock and return true.
		item->SetStock(0);
	}

	else//Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
	{
		balance += quantity * item->GetPrice();//
		item->SetStock(item->GetStock() - quantity);
	}
	return true;

}

