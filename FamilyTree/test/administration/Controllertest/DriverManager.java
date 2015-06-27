package administration.Controllertest;

public class DriverManager {

	private static Connection connection = new Connection();
	
	public static Connection getConnection (String a, String b, String c){
		
		return connection ;
			
	}
	
	public void setConnection (Connection a){
		
		connection = a ;
	}

}
