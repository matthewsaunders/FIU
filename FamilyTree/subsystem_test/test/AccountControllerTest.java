package test;

import static org.junit.Assert.*;

import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.Connection;
import java.sql.SQLWarning;
import java.sql.Statement;
import java.util.ArrayList;

import org.junit.Test;

import account.models.Administration;
import account.models.test.User;
import account.models.test.getUserRow;

public class AccountControllerTest {
	private Facade myFacade = new Facade();

	@Test
	public void doRegistration_Registration_SunnyCase() throws SQLException {
		ConnectionStub cStub = new ConnectionStub();
		PreparedStatementStub.setNull = false;// static variable

		myFacade.SetConnectionStub(cStub);

		// A&S-001R-Subsystem Test-01
		assertTrue(myFacade.doRegistration("Jane", "Doe", "jdoe@gmail.com",
				"money"));
		assertTrue(myFacade.doRegistration("Mary", "Doe", "mdoe@gmail.com",
				"cat"));
		assertTrue(myFacade.doRegistration("Danna", "Doe", "ddoe@gmail.com",
				"chair"));
	}

	@Test
	public void doRegistration_Registration_RainyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		PreparedStatementStub.setNull = true;// static variable

		myFacade.SetConnectionStub(cStub);

		// A&S-001R-Subsystem Test-01
		assertFalse(myFacade.doRegistration("Jaimy", "Doe", "jdoe@gmail.com",
				"miami"));
		assertFalse(myFacade.doRegistration("Melissa", "Doe", "mdoe@gmail.com",
				"laptop"));
		assertFalse(myFacade.doRegistration("Dora", "Doe", "ddoe@gmail.com",
				"pass123"));
	}

	@Test
	public void doLogingAndOut_LogingAndOut_SunnyCase() throws SQLException {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		PreparedStatementStub.setNull = false;

		ResultSetStub.username = "jdoe@gmail.com";
		ResultSetStub.password = "cat";
		ResultSetStub.counter = 2;

		myFacade.SetConnectionStub(cStub);

		// A&S-002L-Subsystem Test-05
		assertTrue(myFacade.doLogin("jdoe@gmail.com", "cat"));

		// preconditions
		ResultSetStub.username = "mdoe@gmail.com";
		ResultSetStub.password = "dog";
		ResultSetStub.counter = 2;

		assertTrue(myFacade.doLogin("mdoe@gmail.com", "dog"));

		// preconditions
		ResultSetStub.username = "ddoe@gmail.com";
		ResultSetStub.password = "horse";
		ResultSetStub.counter = 2;
		assertTrue(myFacade.doLogin("ddoe@gmail.com", "horse"));
	}

	@Test
	public void doLogingAndOut_LogingAndOut_RainyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub.setNull = true;// static variable

		myFacade.SetConnectionStub(cStub);

		// A&S-002L-Subsystem Test-05
		assertFalse(myFacade.doLogin("jdoe@gmail.com", ""));
		assertFalse(myFacade.doLogin("mdoe@gmail.com", ""));
		assertFalse(myFacade.doLogin("ddoe@gmail.com", ""));
	}

	@SuppressWarnings("deprecation")
	@Test
	public void getUserInfo_GetUserRow_SunnyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub.setNull = false;// static variable

		myFacade.SetConnectionStub(cStub);

		getUserRow.connection = new ConnectionStub();

		// preconditions
		ResultSetStub.username = "jdoe@gmail.com";
		ResultSetStub.fname = "john";
		ResultSetStub.lname = "doe";
		ResultSetStub.privileges = "u";
		ResultSetStub.counter = 4;

		// A&S-002L-Subsystem Test-05
		String[] content1 = { "jdoe@gmail.com", "john", "doe", "u" };
		assertEquals(content1, myFacade.getUserInfo("jdoe@gmail.com"));

		ResultSetStub.username = "mdoe@gmail.com";
		ResultSetStub.fname = "martin";
		ResultSetStub.lname = "doe";
		ResultSetStub.privileges = "u";
		ResultSetStub.counter = 4;

		String[] content2 = { "mdoe@gmail.com", "martin", "doe", "u" };
		assertEquals(content2, myFacade.getUserInfo("mdoe@gmail.com"));

		ResultSetStub.username = "ddoe@gmail.com";
		ResultSetStub.fname = "danny";
		ResultSetStub.lname = "doe";
		ResultSetStub.privileges = "u";
		ResultSetStub.counter = 4;

		String[] content3 = { "ddoe@gmail.com", "danny", "doe", "u" };
		assertEquals(content3, myFacade.getUserInfo("ddoe@gmail.com"));
	}

	@Test
	public void getUserInfo_GetUserRow_RainyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub.setNull = true;// information not found in
												// database

		myFacade.SetConnectionStub(cStub);

		String[] row = new String[4];
		assertEquals(row, myFacade.getUserInfo("jdoe@gmail.com"));
		assertEquals(row, myFacade.getUserInfo("mdoe@gmail.com"));
		assertEquals(row, myFacade.getUserInfo("ddoe@gmail.com"));
	}

	@SuppressWarnings("deprecation")
	@Test
	public void findNoAdmin_Administration_SunnyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub psStub = new PreparedStatementStub();
		ResultSetStub rsStub = new ResultSetStub();

		myFacade.SetConnectionStub(cStub);
		myFacade.SetPreparedStatementStub(psStub);
		myFacade.SetResultSetStub(rsStub);
		PreparedStatementStub.setNull = false;// information not found in
												// database

		// preconditions
		ResultSetStub.username = "jdoe@gmail.com";
		ResultSetStub.fname = "john";
		ResultSetStub.lname = "doe";
		ResultSetStub.privileges = "u";
		ResultSetStub.counter = 4;

		ArrayList<User> nonAdmin = new ArrayList<User>();
		nonAdmin.add(new User("jdoe@gmail.com", "john", "doe", "u"));
		assertEquals(nonAdmin, myFacade.findNoAdmin());

		/*
		 * ResultSetStub.username = "mdoe@gmail.com"; ResultSetStub.fname =
		 * "martin"; ResultSetStub.lname = "doe"; ResultSetStub.privileges =
		 * "u"; ResultSetStub.counter = 4;
		 * 
		 * ArrayList<User> nonAdmin2 = new ArrayList<User>(); nonAdmin2.add(new
		 * User("mdoe@gmail.com","martin","doe","u"));
		 * assertEquals(nonAdmin2.get(0), myFacade.findNoAdmin().get(0));
		 * 
		 * ResultSetStub.username = "ddoe@gmail.com"; ResultSetStub.fname =
		 * "danny"; ResultSetStub.lname = "doe"; ResultSetStub.privileges = "u";
		 * ResultSetStub.counter = 4;
		 * 
		 * ArrayList<User> nonAdmin3 = new ArrayList<User>(); nonAdmin3.add(new
		 * User("ddoe@gmail.com","danny","doe","u"));
		 * assertEquals(nonAdmin3.get(0), myFacade.findNoAdmin().get(0));
		 */
	}

	@Test
	public void findNoAdmin_Administration_RainyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub psStub = new PreparedStatementStub();
		ResultSetStub rsStub = new ResultSetStub();

		myFacade.SetConnectionStub(cStub);
		myFacade.SetPreparedStatementStub(psStub);
		myFacade.SetResultSetStub(rsStub);
		PreparedStatementStub.setNull = true;// information not found in
												// database

		myFacade.SetConnectionStub(cStub);

		ArrayList<User> nonAdmin = new ArrayList<User>();
		assertEquals(nonAdmin, myFacade.findNoAdmin());
	}

	@SuppressWarnings("deprecation")
	@Test
	public void showAdminRequest_Administration_SunnyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub psStub = new PreparedStatementStub();
		ResultSetStub rsStub = new ResultSetStub();

		myFacade.SetConnectionStub(cStub);
		myFacade.SetPreparedStatementStub(psStub);
		myFacade.SetResultSetStub(rsStub);
		PreparedStatementStub.setNull = false;// information not found in
												// database

		// preconditions
		ResultSetStub.requestedby = "jdoe@gmail.com";
		ResultSetStub.username = "jdoe@gmail.com";
		ResultSetStub.fname = "john";
		ResultSetStub.lname = "doe";
		ResultSetStub.counter = 3;

		ArrayList<User> nonAdmin = new ArrayList<User>();
		nonAdmin.add(new User("jdoe@gmail.com", "john", "doe", ""));
		assertEquals(nonAdmin, myFacade.showAdminRequest());
	}

	@Test
	public void showAdminRequest_Administration_RainyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub psStub = new PreparedStatementStub();
		ResultSetStub rsStub = new ResultSetStub();

		myFacade.SetConnectionStub(cStub);
		myFacade.SetPreparedStatementStub(psStub);
		myFacade.SetResultSetStub(rsStub);
		PreparedStatementStub.setNull = true;// information not found in
												// database

		ResultSetStub.counter = 0;

		myFacade.SetConnectionStub(cStub);

		ArrayList<User> nonAdmin = new ArrayList<User>();
		assertEquals(nonAdmin, myFacade.showAdminRequest());
	}

	@Test
	public void makeAdmin_Administration_SunnyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub psStub = new PreparedStatementStub();
		ResultSetStub rsStub = new ResultSetStub();

		myFacade.SetConnectionStub(cStub);
		myFacade.SetPreparedStatementStub(psStub);
		myFacade.SetResultSetStub(rsStub);
		PreparedStatementStub.setNull = false;// information not found in
												// database

		// preconditions
		ResultSetStub.username = "jdoe@gmail.com";
		ResultSetStub.fname = "john";
		ResultSetStub.lname = "doe";
		ResultSetStub.privileges = "u";
		ResultSetStub.counter = 4;

		ArrayList<User> askAdmin = new ArrayList<User>();
		askAdmin.add(new User("jdoe@gmail.com", "john", "doe", "u"));

		assertTrue(myFacade.makeAdmin(askAdmin));
	}

	@Test
	public void makeAdmin_Administration_RainyCase() {
		// Preconditions
		ConnectionStub cStub = new ConnectionStub();
		cStub.UpdatePreparedSatementStub(new PreparedStatementStub());
		PreparedStatementStub psStub = new PreparedStatementStub();
		ResultSetStub rsStub = new ResultSetStub();

		myFacade.SetConnectionStub(cStub);
		myFacade.SetPreparedStatementStub(psStub);
		myFacade.SetResultSetStub(rsStub);
		PreparedStatementStub.setNull = true;// information not found in
												// database

		myFacade.SetConnectionStub(cStub);

		ArrayList<User> nonAdmin = new ArrayList<User>();
		assertFalse(myFacade.makeAdmin(nonAdmin));
	}

}
