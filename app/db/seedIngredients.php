<?php
/*
name VARCHAR(150) PRIMARY KEY,
measurementUnit VARCHAR(100)
*/

$table = "ingredient";
print("<h4>Inserting records into $table</h4>");

//spinach omlette
try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('eggs', 'NULL');";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('butter', 'tablespoon');";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('spinach', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('chopped tomatoes', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('salt', 'teaspoon');";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('shredded swiss cheese', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('pepper', 'teaspoon');";
	$conn->exec($sql);
	print("....Inserted Record 7<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 7<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//pancakes
try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('all-purpose flour', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 8<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 8<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('baking powder', 'tablespoon');";
	$conn->exec($sql);
	print("....Inserted Record 9<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 9<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('white sugar', 'teaspoon');";
	$conn->exec($sql);
	print("....Inserted Record 10<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 10<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('milk', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 11<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 11<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('blueberries', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 12<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 12<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//cookies
try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('unsalted butter', 'sticks');";
	$conn->exec($sql);
	print("....Inserted Record 13<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 13<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('brown sugar', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 13<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 13<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('granulated sugar', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 14<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 14<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('vanilla extract', 'tablespoons');";
	$conn->exec($sql);
	print("....Inserted Record 15<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 15<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('baking soda', 'teaspoon');";
	$conn->exec($sql);
	print("....Inserted Record 16<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 16<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('milk chocolate chips', 'cup');";
	$conn->exec($sql);
	print("....Inserted Record 17<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 17<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//chicken
try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('skinless boneless chicken breast halves', 'NULL');";
	$conn->exec($sql);
	print("....Inserted Record 18<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 18<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('olive oil', 'teaspoon');";
	$conn->exec($sql);
	print("....Inserted Record 19<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 19<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('ground cumin', 'teaspoon');";
	$conn->exec($sql);
	print("....Inserted Record 20<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 20<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//pizza
try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('round pizza dough', 'inch');";
	$conn->exec($sql);
	print("....Inserted Record 21<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 21<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('pizza sauce', 'tablespoon');";
	$conn->exec($sql);
	print("....Inserted Record 21<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 21<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('fresh mozzarella', 'ounces');";
	$conn->exec($sql);
	print("....Inserted Record 22<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 22<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, measurementUnit)
		VALUES('basil leaves', 'NULL');";
	$conn->exec($sql);
	print("....Inserted Record 23<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 23<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

?>