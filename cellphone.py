import os
import json
from datetime import datetime, timedelta
import time

# Data Structures
class Request:
    def __init__(self, cname="", cnum="", brand="", model="", issue="", dtype="", priority="",
                 status="", date="", time="", estimate="", rate=0):
        self.cname = cname
        self.cnum = cnum
        self.brand = brand
        self.model = model
        self.issue = issue
        self.dtype = dtype
        self.priority = priority
        self.status = status
        self.date = date
        self.time = time
        self.estimate = estimate
        self.rate = rate

cellphone = []  # Pending requests
cancel = []     # Cancelled requests
complete = []   # Completed requests
id_counter = 0  # Ticket ID counter
comid = 0  # Counter for completed requests
canid = 0  # Counter for cancelled requests

# Utilities
def get_current_datetime(format="%Y-%m-%d %H:%M:%S"):
    """Get current date and time as a formatted string."""
    return datetime.now().strftime(format)


# File Handling Functions
def load_requests(file_name, target_list, id_key):
    """Load requests from a file."""
    global id_counter
    if not os.path.exists(file_name):
        return
    with open(file_name, "r") as file:
        data = json.load(file)
        id_counter = data.get(id_key, 0)
        target_list.extend([Request(**req) for req in data.get("requests", [])])


def save_requests(file_name, target_list, id_key):
    """Save requests to a file."""
    global id_counter
    data = {
        id_key: id_counter,
        "requests": [vars(req) for req in target_list],
    }
    with open(file_name, "w") as file:
        json.dump(data, file, indent=4)


# Load Functions
def load_pending():
    """Load pending requests."""
    load_requests("customerticket.json", cellphone, "id_counter")


def load_cancel():
    """Load cancelled requests."""
    load_requests("cancelled.json", cancel, "canid")


def load_complete():
    """Load completed requests."""
    load_requests("completed.json", complete, "comid")


# Save Functions
def save_pending():
    """Save pending requests."""
    save_requests("customerticket.json", cellphone, "id_counter")


def save_cancel():
    """Save cancelled requests."""
    save_requests("cancelled.json", cancel, "canid")


def save_complete():
    """Save completed requests."""
    save_requests("completed.json", complete, "comid")


# Ticket Creation Function
def create_ticket():
    """Create a new ticket and save it."""
    global cellphone, id_counter

    os.system("cls" if os.name == "nt" else "clear")

    print("\n" * 3)
    print("+" + "-" * 40 + "+")
    print("|         Create New Ticket         |")
    print("+" + "-" * 40 + "+")
    print("| Please Provide the following details: |")
    print("+" + "-" * 40 + "+")

    cname = input("Customer Name: ").strip()
    cnum = input("Contact Number: ").strip()
    dtype = input("Device Type: ").strip()
    brand = input("Brand: ").strip()
    model = input("Model: ").strip()
    issue = input("Issue: ").strip()

    # Priority input
    while True:
        priority = input("Priority (type [q] Major or [e] Minor): ").lower().strip()
        if priority == 'q':
            priority = "Major"
            break
        elif priority == 'e':
            priority = "Minor"
            break
        else:
            print("Invalid input, please try again.")

    # Get estimated time to finish
    estimate = input("Estimated Date & Time to Finish: ").strip()

    # Auto-fill other fields
    current_date = get_current_datetime("%Y-%m-%d")
    current_time = get_current_datetime("%H:%M:%S")

    # Create the ticket
    new_ticket = Request(
        cname=cname,
        cnum=cnum,
        brand=brand,
        model=model,
        issue=issue,
        dtype=dtype,
        priority=priority,
        status="Ongoing",
        date=current_date,
        time=current_time,
        estimate=estimate
    )

    # Add ticket to the list
    cellphone.append(new_ticket)
    id_counter += 1

    # Save to file
    save_pending()

    print("\n\nTicket Created Successfully!")
    time.sleep(3)

def view_requests():
    os.system("cls" if os.name == "nt" else "clear")
    """Display all ongoing requests in a formatted table."""
    global cellphone

    if not cellphone:
        print("\n" + " " * 40 + "+----------------------------------+")
        print(" " * 40 + "|  No ongoing requests to display! |")
        print(" " * 40 + "+----------------------------------+")
        input(" " * 40 + "Press Enter to return to the main menu...")
        return

    # Table header
    print("\n" + "+" + "-" * 5 + "+" + "-" * 22 + "+" + "-" * 15 + "+" + "-" * 15 + "+" + "-" * 15 + "+"
          + "-" * 20 + "+" + "-" * 32 + "+" + "-" * 12 + "+" + "-" * 10 + "+" + "-" * 12 + "+" + "-" * 10 + "+"
          + "-" * 22 + "+")
    print("| " + f"{'ID':<3}" + " | " + f"{'Customer Name':<20}" + " | " + f"{'Contact No.':<13}" + " | "
          + f"{'Device Type':<13}" + " | " + f"{'Brand':<13}" + " | " + f"{'Model':<18}" + " | "
          + f"{'Issue':<30}" + " | " + f"{'Priority':<10}" + " | " + f"{'Status':<8}" + " | "
          + f"{'Date':<10}" + " | " + f"{'Time':<8}" + " | " + f"{'EST Date & Time':<20}" + " |")
    print("+" + "-" * 5 + "+" + "-" * 22 + "+" + "-" * 15 + "+" + "-" * 15 + "+" + "-" * 15 + "+"
          + "-" * 20 + "+" + "-" * 32 + "+" + "-" * 12 + "+" + "-" * 10 + "+" + "-" * 12 + "+" + "-" * 10 + "+"
          + "-" * 22 + "+")

    # Table rows
    for idx, req in enumerate(cellphone):
        print("| " + f"{idx + 1:<3}" + " | " + f"{req.cname:<20}" + " | " + f"{req.cnum:<13}" + " | "
              + f"{req.dtype:<13}" + " | " + f"{req.brand:<13}" + " | " + f"{req.model:<18}" + " | "
              + f"{req.issue:<30}" + " | " + f"{req.priority:<10}" + " | " + f"{req.status:<8}" + " | "
              + f"{req.date:<10}" + " | " + f"{req.time:<8}" + " | " + f"{req.estimate:<20}" + " |")
        print("+" + "-" * 5 + "+" + "-" * 22 + "+" + "-" * 15 + "+" + "-" * 15 + "+" + "-" * 15 + "+"
              + "-" * 20 + "+" + "-" * 32 + "+" + "-" * 12 + "+" + "-" * 10 + "+" + "-" * 12 + "+"
              + "-" * 10 + "+" + "-" * 22 + "+")

def update_ticket():
    os.system("cls" if os.name == "nt" else "clear")
    view_requests()
    try:
        num = int(input("\nEnter ID to update (or 0 to exit): "))
        if num == 0:
            return
        if num < 1 or num > len(cellphone):
            raise ValueError

        index = num - 1
        selected_ticket = cellphone[index]

        while True:
            os.system("cls" if os.name == "nt" else "clear")
            print(f"Updating Request ID: {num}")
            print("\n1. Customer Name\n2. Contact No.\n3. Device Type\n4. Brand\n5. Model\n6. Issue")
            print("7. Priority\n8. Estimated Date & Time\n9. Update All\n10. Go Back")
            opt = input("\nEnter your choice: ")

            if opt == "1":
                selected_ticket.cname = input("Enter new Customer Name: ").strip()
            elif opt == "2":
                selected_ticket.cnum = input("Enter new Contact No.: ").strip()
            elif opt == "3":
                selected_ticket.dtype = input("Enter new Device Type: ").strip()
            elif opt == "4":
                selected_ticket.brand = input("Enter new Brand: ").strip()
            elif opt == "5":
                selected_ticket.model = input("Enter new Model: ").strip()
            elif opt == "6":
                selected_ticket.issue = input("Enter new Issue: ").strip()
            elif opt == "7":
                selected_ticket.priority = input("Enter new Priority: ").strip()
            elif opt == "8":
                selected_ticket.estimate = input("Enter new Estimated Date & Time: ").strip()
            elif opt == "9":
                selected_ticket.cname = input("Enter new Customer Name: ").strip()
                selected_ticket.cnum = input("Enter new Contact No.: ").strip()
                selected_ticket.dtype = input("Enter new Device Type: ").strip()
                selected_ticket.brand = input("Enter new Brand: ").strip()
                selected_ticket.model = input("Enter new Model: ").strip()
                selected_ticket.issue = input("Enter new Issue: ").strip()
                selected_ticket.priority = input("Enter new Priority: ").strip()
                selected_ticket.estimate = input("Enter new Estimated Date & Time: ").strip()
            elif opt == "10":
                break
            else:
                print("Invalid choice! Try again.")
                continue

            save_pending()  # Save changes to the file
            print("\nRequest updated successfully!")
            time.sleep(3)
            break
    except ValueError:
        print("Invalid input! Please enter a valid ID.")
        time.sleep(2)

def payment_menu():
    while True:
        os.system("cls" if os.name == "nt" else "clear")
        print("\n\n\n\n\n")
        print(" " * 30 + "+----------------------------------+")
        print(" " * 30 + "|      Please select an option:    |")
        print(" " * 30 + "+----------------------------------+")
        print(" " * 30 + "| 1. Payment                       |")
        print(" " * 30 + "| 2. Transaction History           |")
        print(" " * 30 + "| 3. Go Back                       |")
        print(" " * 30 + "+----------------------------------+")
        choice = input(" " * 30 + "| Enter your choice:               |\n" + " " * 30 + "| > ")

        if choice == "1":
            collect_payment()
        #elif choice == "2":
        #    view_complete_requests()
        elif choice == "3":
            break
        else:
            print("\n\n")
            print(" " * 30 + "+----------------------------------+")
            print(" " * 30 + "|         Invalid choice!          |")
            print(" " * 30 + "+----------------------------------+")
            time.sleep(2)

def collect_payment():
    global comid, canid

    os.system("cls" if os.name == "nt" else "clear")
    print("\n\nRequests:")
    view_requests()

    try:
        num = int(input("\n\n" + " " * 30 + "+-------------------------------------+\n" +
                        " " * 30 + "| Select an ID or Enter [0] to exit:  |\n" +
                        " " * 30 + "| > "))
    except ValueError:
        print("\nInvalid input! Please enter a number.")
        time.sleep(2)
        return

    if num == 0:
        return

    if num < 1 or num > len(cellphone):
        print("\n\n" + " " * 30 + "+----------------------------------+")
        print(" " * 30 + "|          ID not found!           |")
        print(" " * 30 + "+----------------------------------+")
        time.sleep(3)
        return

    index = num - 1
    selected_request = cellphone[index]

    while True:
        print("\n\n" + " " * 30 + "+-------------------------------------+")
        print(" " * 30 + "| Type [y] for Completed or [n] for Cancelled |")
        done = input(" " * 30 + "| > ").lower()
        print(" " * 30 + "+-------------------------------------+")

        if done == "y":
            selected_request.status = "Completed"
            selected_request.date = get_current_datetime("%m-%d-%Y")
            selected_request.time = get_current_datetime("%I:%M %p")
            comid += 1
            complete.append(selected_request)
            cellphone.pop(index)
            save_pending()  # Save pending list after removal
            print("\n\n" + " " * 30 + "+----------------------------------+")
            print(" " * 30 + "| Ticket completed successfully!   |")
            print(" " * 30 + "+----------------------------------+")
            time.sleep(3)
            break
        elif done == "n":
            selected_request.status = "Cancelled"
            selected_request.date = get_current_datetime("%m-%d-%Y")
            selected_request.time = get_current_datetime("%I:%M %p")
            canid += 1
            cancel.append(selected_request)
            cellphone.pop(index)
            save_pending()  # Save pending list after removal
            print("\n\n" + " " * 30 + "+----------------------------------+")
            print(" " * 30 + "| Ticket cancelled successfully!   |")
            print(" " * 30 + "+----------------------------------+")
            time.sleep(3)
            break
        else:
            print("Invalid input! Please type [y] or [n].")
            continue


def main_menu():
    global id_counter

    while True:
        os.system("cls" if os.name == "nt" else "clear")
        print("\n" + " " * 40 + "+----------------------------------+")
        print(" " * 40 + "|            WELCOME               |")
        print(" " * 40 + "+----------------------------------+")
        print(" " * 40 + "| Please select an option:         |")
        print(" " * 40 + "|                                  |")
        print(" " * 40 + "| 1. Create a New Ticket           |")
        print(" " * 40 + "| 2. View All Ongoing Requests     |")
        print(" " * 40 + "| 3. Update Ticket                 |")
        print(" " * 40 + "| 4. Payment & Request History     |")
        print(" " * 40 + "| 5. Settings                      |")
        print(" " * 40 + "| 6. Exit                          |")
        print(" " * 40 + "+----------------------------------+")
        choice = input(" " * 40 + "| Enter your choice: > ")

        if choice == "1":
            create_ticket()
        elif choice == "2":
            view_requests()
            input("\nPress Enter to return to the main menu...")
        elif choice == "3":
            update_ticket()
        elif choice == "4":
            payment_menu()
        #elif choice == "5":
        #   settings()
        elif choice == "6":
            print("\n" + " " * 40 + "+----------------------------------+")
            print(" " * 40 + "|       Thank you! Exiting..       |")
            print(" " * 40 + "+----------------------------------+")
            time.sleep(3)
            exit(0)
        else:
            print("\n" + " " * 40 + "+----------------------------------+")
            print(" " * 40 + "|         Invalid choice!          |")
            print(" " * 40 + "+----------------------------------+")
            time.sleep(2)

if __name__ == "__main__":
    load_pending()
    load_cancel()
    load_complete()
    main_menu()