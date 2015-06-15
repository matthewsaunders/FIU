package test;

public class DriverManagerStub
{
	
	public static ConnectionStub getConnection(String connectionURL, String dbUsername,
			String dbPassword) 
	{
		return new ConnectionStub();
	}
}
