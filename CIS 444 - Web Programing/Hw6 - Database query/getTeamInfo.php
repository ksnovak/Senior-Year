<!doctype html>
<html lang="en">
<head>
	<title>NFL team lookup</title>
	<meta charset="utf-8">
	
	<style>
		table, tr, td {
			border: 1px solid black;
		}
	</style>
</head>

<body>
<?php

	
	$DBConnect = @mysql_connect ('localhost', 'novak009', 'novak009')
		Or die("<p>ERROR: The database server is not available.</p>" . "<p>Error Code " . mysql_connect_errno() . ": " . mysql_connect_error() . "<p>");
	echo "<p>SUCCESS: Connected to server</p>";
	
	@mysql_select_db('novak009')
		Or die("<p>ERROR: Database could not be found</p>" . "<p>Error Code " . mysql_connect_errno() . ": " . mysql_connect_error() . "<p>");
	echo "<p>SUCCESS: Connected to database</p>";

	$TeamID = $_GET['idInput'];
	$QueryString = "SELECT * FROM teams where teamId='" . $TeamID . "';";
	$QueryResult = @mysql_query($QueryString);
	$Rows = mysql_num_rows($QueryResult);
	$Cols = mysql_num_fields($QueryResult);

	if (mysql_num_rows($QueryResult)) //If there is a result
	{	
		echo "<table>";
		echo "<tr> <td>Team ID</td> <td>Team name</td> <td>Start year</td> <td>Owner name</td> <td>GM name</td> <td>Coach name</td> <td>Starting QB</td> <td>Office Address</td> <td>City</td> <td>State</td> <td>Zip</td> <td>Phone</td> <td>Overall record</td> <td>Conference record</td></tr>"; //Print field names
		
		while ($Row = mysql_fetch_array($QueryResult)) //Go through results
		{			
			echo "<tr>";
			for ($i = 0; $i < mysql_num_fields($QueryResult); $i++)//Go through each attribute
			{
				echo "<td>" . $Row[$i] . "</td>";
			}
			echo "</tr>";
		}
		echo "</table";
	}
	else
		echo "<p>WARNING: No search results </p>";

mysql_close($DBConnect);
?>
</body>