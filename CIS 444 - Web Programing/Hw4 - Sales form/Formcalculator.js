//Easy access to html elements
function $(x) {	return document.getElementById(x);}

//Constants for easy modification
var APPLECOST = 0.59;
var ORANGECOST = 0.49;
var BANANACOST = 0.39;

//Summations that get altered within the update function.
var subtotal = 0;
var tax = 0;
var total = 0;


function updatetotal(event) 
{
	//Check for invalid values.
	if (event.target.value > 99 || event.target.value < 0)
	{
		alert("Invalid quantity. Try again.");
		event.target.value = "";
		event.target.focus();
	}
	else
	{
		subtotal = $('appleQuantity').value * APPLECOST 	+	$('orangeQuantity').value * ORANGECOST 	+	$('bananaQuantity').value * BANANACOST;
		$('subtotal').innerHTML = "$" + subtotal.toFixed(2);
		
		tax = subtotal * 0.05;
		$('tax').innerHTML = "+ $" + tax.toFixed(2);
		
		total = (tax + subtotal).toFixed(2);
		$('total').innerHTML = "$" + total;
	}
	return false;
}


function submitPurchase()
{
	alert ("Your order will be $" + total +". Thank you!");
	return false;
}
