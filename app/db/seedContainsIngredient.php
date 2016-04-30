<?php
/*
recipeId INT(11),
ingredientName VARCHAR(150),
amount INT NOT NULL,
PRIMARY KEY(recipeId,ingredientName)
*/

$table = "containsIngredient";
print("<h4>Inserting records into $table</h4>");

//omlette
try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'eggs', '2');";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'butter', '1');";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'spinach', '1');";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'chopped tomatoes', '1/3');";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'salt', '1/8');";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'shredded swiss cheese', '1/3');";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'pepper', '1/8');";
	$conn->exec($sql);
	print("....Inserted Record 7<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 7<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//pancakes
try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'all-purpose flour', '1 1/4');";
	$conn->exec($sql);
	print("....Inserted Record 8<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 8<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'salt', '1/2');";
	$conn->exec($sql);
	print("....Inserted Record 9<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 9<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'baking powder', '1');";
	$conn->exec($sql);
	print("....Inserted Record 10<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 10<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'white sugar', '1 1/4');";
	$conn->exec($sql);
	print("....Inserted Record 11<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 11<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'eggs', '1');";
	$conn->exec($sql);
	print("....Inserted Record 10<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 10<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'milk', '1');";
	$conn->exec($sql);
	print("....Inserted Record 12<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 12<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'butter', '1/2');";
	$conn->exec($sql);
	print("....Inserted Record 13<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 13<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(2, 'blueberries', '1/2');";
	$conn->exec($sql);
	print("....Inserted Record 14<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 14<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//cookies
try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'unsalted butter', '2');";
	$conn->exec($sql);
	print("....Inserted Record 15<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 15<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'brown sugar', '1');";
	$conn->exec($sql);
	print("....Inserted Record 16<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 16<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'granulated sugar', '1/3');";
	$conn->exec($sql);
	print("....Inserted Record 17<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 17<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'eqqs', '2');";
	$conn->exec($sql);
	print("....Inserted Record 18<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 18<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'vanilla extract', '2');";
	$conn->exec($sql);
	print("....Inserted Record 19<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 19<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'all-purpose flour', '2 1/2');";
	$conn->exec($sql);
	print("....Inserted Record 20<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 20<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'baking powder', '1');";
	$conn->exec($sql);
	print("....Inserted Record 21<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 21<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'baking soda', '1');";
	$conn->exec($sql);
	print("....Inserted Record 22<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 22<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'salt', '3/4');";
	$conn->exec($sql);
	print("....Inserted Record 23<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 23<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(3, 'milk chocolate chips', '2');";
	$conn->exec($sql);
	print("....Inserted Record 24<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 24<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//chicken
try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(4, 'skinless boneless chicken breast halves', '4');";
	$conn->exec($sql);
	print("....Inserted Record 25<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 25<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(4, 'olive oil', '4');";
	$conn->exec($sql);
	print("....Inserted Record 27<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 27<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(4, 'ground cumin', '1');";
	$conn->exec($sql);
	print("....Inserted Record 28<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 28<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(4, 'salt', '1/2');";
	$conn->exec($sql);
	print("....Inserted Record 29<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 29<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(4, 'pepper', '1/4');";
	$conn->exec($sql);
	print("....Inserted Record 30<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 30<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

//pizza
try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(5, 'round pizza dough', '12');";
	$conn->exec($sql);
	print("....Inserted Record 31<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 31<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(5, 'tomatoe sauce', '3');";
	$conn->exec($sql);
	print("....Inserted Record 32<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 32<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(5, 'olive oil', 'NULL');";
	$conn->exec($sql);
	print("....Inserted Record 33<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 33<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(5, 'mozzarella', '2 3/4');";
	$conn->exec($sql);
	print("....Inserted Record 34<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 34<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(5, 'basil leaves', '4 to 5');";
	$conn->exec($sql);
	print("....Inserted Record 35<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 35<br>");
	//print("    ".print($e->getMessage()."<br>"));
}












































?>