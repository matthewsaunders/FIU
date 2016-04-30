<?php
/*
ID INT(11) AUTO_INCREMENT PRIMARY KEY,
name VARCHAR(150),
author VARCHAR(100) NOT NULL);
*/

$table = "cookbook";
print("<h4>Inserting records into $table</h4>");

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(1 ,'breakfast', 'John Doe');";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(2, 'lunch', 'John Doe');";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(3, 'dinner', 'John Doe');";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(4, 'Pizza', 'Jane Doe');";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(5, 'desert', 'Jane Doe');";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(6, 'dinner', 'John Doe');";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(7, 'Cena', 'Leo Martin');";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (id, name, author)
		VALUES(8, 'Desayuno', 'Matthew Saunders');";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}













?>