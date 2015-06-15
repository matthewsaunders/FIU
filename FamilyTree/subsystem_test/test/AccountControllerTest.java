package test;

import static org.junit.Assert.*;

import java.sql.SQLException;

import org.junit.Test;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.MySQLConnection;
import com.mysql.jdbc.PreparedStatement;

public class AccountControllerTest 
{


	private Facade myFacade = new Facade();
	
	@Test
	public void unregisterUserRegistration_SuccessfulRegistration_SunnyCase() throws SQLException
	{
		//Preconditions
		ResultSetStub rs = new ResultSetStub();
		PreparedStatementStub ps = new PreparedStatementStub();				
		
		myFacade.SetConnectionStub(new ConnectionStub());//Establish connection with DB
		myFacade.SetResultSetStub(rs);	
		ps.SetResultSet(rs);
		myFacade.SetPreparedStatementStub(ps);
		
		
		//A&S-001R-Subsystem Test-01
		assertTrue("true", myFacade.doRegistration("Jane", "Doe", "jdoe@gmail.com", "money"));
		assertTrue("true", myFacade.doRegistration("Mary", "Doe", "mdoe@gmail.com", "cat"));
		assertTrue("true", myFacade.doRegistration("Danna", "Doe", "ddoe@gmail.com", "chair"));
	}
	
	
	/*@Test
	public void unregisterUserRegistration_SuccessfulRegistration_RainyCase()
	{
		//Preconditions
		
				
		//A&S-001R-Subsystem Test-01		
		assertFalse("false", myFacade.doRegistration("Jaimy", "Doe", "jaimydoe@gmail.com", "miami"));
		assertFalse("false", myFacade.doRegistration("Melissa", "Doe", "melissadoe@gmail.com", "laptop"));
		assertFalse("false", myFacade.doRegistration("Dora", "Doe", "doradoe@gmail.com", "pass123"));
	}
	
	@Test
	public void unregisterUserRegistration_IncorrectInput_SunnyCase()
	{
		//A&S-002R-Subsystem Test-02
		assertFalse("false", myFacade.doRegistration("Alexa", "Eggert", "alexaegmail.com", "pink"));
		assertFalse("false", myFacade.doRegistration("Aurora", "Cotter", "aurora", ""));
		assertFalse("false", myFacade.doRegistration("Dora", "Eggert", "@gmail.com", ""));
	}*/
	
	/*@Test
	public void unregisterUserRegistration_IncorrectInput_RainyCase()
	{
		//A&S-002R-Subsystem Test-02
		assertTrue("true", myFacade.doRegistration("Sindy", "Doe", "sindydoe@gmail.com", "money"));
		assertTrue("true", myFacade.doRegistration("Maria", "Doe", "mariadoe@gmail.com", "cat"));
		assertTrue("true", myFacade.doRegistration("Luisa", "Doe", "luisadoe@gmail.com", "chair"));
	}
	
	@Test
	public void unregisterUserRegistration_DuplicateEmail_SunnyCase()
	{
		//A&S-003R-Subsystem Test-03
		assertFalse("false", myFacade.doRegistration("Jaimy", "Doe", "jdoe@gmail.com", "miami"));
		assertFalse("false", myFacade.doRegistration("Melissa", "Doe", "mdoe@gmail.com", "laptop"));
		assertFalse("false", myFacade.doRegistration("Dora", "Doe", "ddoe@gmail.com", "pass123"));
	}
	
	@Test
	public void unregisterUserRegistration_DuplicateEmail_RainyCase()
	{
		
		//A&S-003R-Subsystem Test-03
		assertTrue("true", myFacade.doRegistration("Jane", "Doe", "jdoe@gmail.com", "money"));
		assertTrue("true", myFacade.doRegistration("Mary", "Doe", "mdoe@gmail.com", "cat"));
		assertTrue("true", myFacade.doRegistration("Melissa", "Doe", "mdoe@gmail.com", "chair"));
	}
	
	@Test
	public void registeredUserLogin_LoginSuccess_SunnyCase()
	{
		//A&S-001L-Subsystem Test-04
		assertTrue("true", myFacade.doLogin("jdoe@gmail.com", "money"));
		assertTrue("true", myFacade.doLogin("mdoe@gmail.com", "cat"));
		assertTrue("true", myFacade.doLogin("ddoe@gmail.com", "chair"));
	}
	
	@Test
	public void registeredUserLogin_LogingSuccess_RainyCase()
	{
		
		//A&S-001L-Subsystem Test-04
		assertFalse("false", myFacade.doLogin("jdoe@gmail.com", "dinero"));
		assertFalse("false", myFacade.doLogin("mdoe@gmail.com", "gato"));
		assertFalse("false", myFacade.doLogin("ddoe@gmail.com", "silla"));
	}
	
	@Test
	public void registeredUserLogin_LogingUnsuccessful_SunnyCase()
	{
		
		//A&S-002L-Subsystem Test-05
		assertFalse("false", myFacade.doLogin("jdoe@gmail.com", ""));
		assertFalse("false", myFacade.doLogin("mdoe@gmail.com", ""));
		assertFalse("false", myFacade.doLogin("ddoe@gmail.com", ""));
	}
	
	@Test
	public void registeredUserLogin_LoginUnsuccessful_RainyCase()
	{
		//A&S-002L-Subsystem Test-05
		assertTrue("true", myFacade.doLogin("jdoe@gmail.com", "money"));
		assertTrue("true", myFacade.doLogin("mdoe@gmail.com", "cat"));
		assertTrue("true", myFacade.doLogin("ddoe@gmail.com", "chair"));
	}
	*/
}
