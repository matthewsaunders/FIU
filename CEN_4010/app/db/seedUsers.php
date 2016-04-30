<?php
/*
CREATE table $table(
		name VARCHAR(150) PRIMARY KEY,
		email VARCHAR(255) NOT NULL,
		password VARCHAR(50) NOT NULL,
		adminStatus CHAR(1) NOT NULL)
*/

$table = "users";
print("<h4>Inserting records into $table</h4>");

try{
	$sql = "INSERT INTO $table (name, email, password, adminStatus)
		VALUES('John Doe', 'john.doe@yahoo.com', 'password123', 'N');";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, email, password, adminStatus)
		VALUES('Jane Doe', 'jane.doe@yahoo.com', 'passwordABC', 'N');";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, email, password, adminStatus)
		VALUES('admin', 'admin@cookbook.com', 'admin123', 'Y');";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, email, password, adminStatus)
		VALUES('Matthew Saunders', 'msaun008@fiu.edu', 'password', 'N');";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (name, email, password, adminStatus)
		VALUES('Leo Martin', 'lmart296@fiu.edu', 'password', 'Y');";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

?>