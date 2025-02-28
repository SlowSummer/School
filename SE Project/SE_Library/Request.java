package src;

import java.time.LocalDate;
import java.util.Date;

/**
 * The Request class represents a request for an item by a user.
 * It keeps track of the user, the item, the request date,
 * and whether the request has been fulfilled.
 */

public class Request {
    	private static int idCounter = 1;	// Static counter to assign unique IDs to each request
    	private int requestId;			// Unique ID for this request
    	private User user;			// The user requesting the item
    	private Item item;			// The item being requested
    	private LocalDate requestDate;		// The date the request was made
    	private boolean fulfilled;		// Whether the request has been fulfilled

	/**
	 * Constructor to create a new request.
	 *
 	 * @param user: The user requesting the item
 	 * @param item: The item being requested
	 * @param requestDate: The date the request was made
	 */
    	public Request(User user, Item item, LocalDate requestDate) {
        	this.requestId = idCounter++;	// Assign a unique ID to this request
        	this.user = user;
        	this.item = item;
        	this.requestDate = requestDate;
        	this.fulfilled = false;		// Initialize the request as not fulfilled
    	}

	// Getter methods for various attributes
    	public int getRequestId() {
        	return requestId;
    	}

    	public User getUser() {
        	return user;
    	}

    	public Item getItem() {
        	return item;
    	}

    	public LocalDate getRequestDate() {
        	return requestDate;
    	}

    	public boolean isFulfilled() {
        	return fulfilled;
    	}

	/**
	 * Marks the request as fulfilled.
	 */
	public void fulfill() {
        	this.fulfilled = true;
    	}
}
