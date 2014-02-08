//Get input from user:

promptUser();

//Get input from user, validate it as a positive integer
function promptUser()
{
	do { 
		var n = parseInt(prompt("Enter an integer"));
	} while (n < 1 || isNaN(n)) //Ensure it is a number and is positive.
	populateTable(n); //Perform summations
}

//Sum from 1 to n.
function populateTable(n)
{
	var total = 0;
	//Start out the table with title rows, before populating it.
	document.write("<table> <tr> <th>Current</th> <th>Sum</th> </tr>");

	//Here is the summation and table population.
	for (var i = 1; i <= n; i++)
	{
		total += i;
		document.write("<tr> <td>" + i + "</td> <td>" + total + "</td> </tr>"); 
		if (i == n)
		{
			document.getElementById("finalValue").innerHTML += " " + total;
			document.getElementById("finalValue").style.visibility = "visible";
		}
	}

	//Make sure to close the table
	document.write("</table>");
}
