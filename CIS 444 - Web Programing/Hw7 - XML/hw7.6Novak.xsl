<?xml version = "1.0" encoding="utf-8"?>
<!-- 7.6 Modify the XSLT style sheet of Exercise 7.5 to format all the car elements in the XML document of Exercise 7.2, and use the style sheet to create a display of the whole document.

NOTE: The document which uses this as a stylesheet is hw7.6Novak.xml.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml">

<xsl:template match="catalog">
	<html><head><title>XSL stylesheet for hw7.6Novak.xml</title></head>
	
	<body style="background-color: #EBFDFF; max-width: 500px;">
		<h2 style="text-align: center;">Cars for sale</h2>
		<xsl:apply-templates />
	</body></html>
	</xsl:template>
	
	<xsl:template match="make">
		<br /> <span style="font-size: 16pt;">Make: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>
	<xsl:template match="model">
		<span style="font-size: 16pt;">Model: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>
	<xsl:template match="year">
		<span style="font-size: 16pt;">Year: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>
	<xsl:template match="color">
		<span style="font-size: 16pt;">Color: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>
	<xsl:template match="number_of_cylinders">
		<xsl:value-of select="." /> 
		<span style="font-size: 16pt;">-cylinder</span> <br />
	</xsl:template>
	<xsl:template match="fuel_system">
		<span style="font-size: 16pt;">Fuel system: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>
	<xsl:template match="number_of_doors">
		<xsl:value-of select="."/> 
		<span style="font-size: 16pt;">-door</span><br />
	</xsl:template>	
	<xsl:template match="transmission_type">
		<span style="font-size: 16pt;">Transmission: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>	
	<xsl:template match="accessories">
		<span style="font-size: 16pt;">Accesories: </span>
		<xsl:value-of select="."/> <br />
	</xsl:template>
</xsl:stylesheet>