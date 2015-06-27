package account.models.test;

public class User {

	String userName;
	String fname;
	String lname;
	String priviledges;

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public String getFname() {
		return fname;
	}

	public void setFname(String fname) {
		this.fname = fname;
	}

	public String getLname() {
		return lname;
	}

	public void setLname(String lname) {
		this.lname = lname;
	}

	public String getPriviledges() {
		return priviledges;
	}

	public void setPriviledges(String priviledges) {
		this.priviledges = priviledges;
	}

	public User(String userName, String fname, String lname, String priviledeges) {
		this.userName = userName;
		this.fname = fname;
		this.lname = lname;
		this.priviledges = priviledeges;

	}

	// A better definition, but still not perfect
	@Override
	public boolean equals(Object other) {
		boolean result = false;
		if (other instanceof User) {
			User that = (User) other;
			result = (this.getUserName() == that.getUserName() && this
					.getLname() == that.getLname());
		}
		return result;
	}

}
