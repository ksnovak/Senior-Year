var marquee, velocity, x, maxX, minX;
minX = 100;
maxX = 500;
function initScroll()
{
	velocity = 1; //Determines whether the statement scrolls right (positive) or left (negative).
	
	marquee = document.getElementById('theText').style;
	marquee.left = "10px";	//For some reason, when you set marquee.left = x + "px";, it adds an extra 0. So 10 -> 100.
	
	x = marquee.left;
	x = x.match(/\d+/);	//This strips out the "px" from the .left value, turning it into just a number.
	scroll(x);
}

function scroll(x) {
	
//We alternate color every 5th step.
if (x%5 == 0)	
{
	if (marquee.color == "red")
		marquee.color = "blue";
	else
		marquee.color = "red";
}

//Determine whether to go left or right.
if (x >= maxX)
	velocity = -1;
else if (x <= minX)
	velocity = 1;

//Change the position	
x += velocity;
marquee.left = x+"px";

//Re-call this function in 5 ms 
setTimeout("scroll(" + x + ")", 5);
}
