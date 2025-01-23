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

tickets = {"pending": [], "canceled": [], "completed": []}
id_counter = 0  # Ticket ID counter
comid = 0
canid = 0

# Utilities
def get_current_datetime(format="%Y-%m-%d %H:%M:%S"):
    """Get current date and time as a formatted string."""
    return datetime.now().strftime(format)


# Load Functions
def load_tickets():
    """Load all tickets from the save file."""
    global tickets, id_counter
    if not os.path.exists("tickets.json"):
        return
    with open("tickets.json", "r") as file:
        data = json.load(file)
        id_counter = data.get("id_counter", 0)
        for key in tickets:
            tickets[key] = [Request(**req) for req in data.get(key, [])]

# Save Functions
def save_tickets():
    """Save all tickets to the save file."""
    global id_counter
    data = {
        "id_counter": id_counter,
        "pending": [vars(req) for req in tickets["pending"]],
        "canceled": [vars(req) for req in tickets["canceled"]],
        "completed": [vars(req) for req in tickets["completed"]],
    }
    with open("tickets.json", "w") as file:
        json.dump(data, file, indent=4)


# Ticket Creation Function
def create_ticket():
    """Create a new ticket and save it."""
    global id_counter

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
        status="Pending",
        date=current_date,
        time=current_time,
        estimate=estimate
    )

    tickets["pending"].append(new_ticket)
    id_counter += 1

    save_tickets()

    print("\n\nTicket Created Successfully!")
    time.sleep(3)

def view_requests(status="pending"):
    os.system("cls" if os.name == "nt" else "clear")
    """Display all ongoing requests in a formatted table."""

    if not tickets["pending"]:
        print("\n" + " " * 40 + "+----------------------------------+")
        print(" " * 40 + f"|  No {status.capitalize()} requests to display! |")
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
    for idx, req in enumerate(tickets["pending"]):
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
        if num < 1 or num > len(tickets["pending"]):
            raise ValueError

        index = num - 1
        selected_ticket = tickets["pending"][index]

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
            
            save_tickets() 
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
        elif choice == "2":
            view_transaction_history()
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
        payment_menu()

    if num == 0:
        payment_menu()

    if num < 1 or num > len(tickets["pending"]):
        print("\n\n" + " " * 30 + "+----------------------------------+")
        print(" " * 30 + "|          ID not found!           |")
        print(" " * 30 + "+----------------------------------+")
        time.sleep(2)
        payment_menu()

    index = num - 1
    selected_request = tickets["pending"][index]

    while True:
        print("\n\n" + " " * 30 + "+-------------------------------------+")
        print(" " * 30 + "| Type [y] for Completed or [n] for Cancelled |")
        done = input(" " * 30 + "| > ").lower()
        print(" " * 30 + "+-------------------------------------+")

        if done == "y":
            selected_request.status = "Completed"
            compute_rate(index)
            selected_request.date = get_current_datetime("%m-%d-%Y")
            selected_request.time = get_current_datetime("%I:%M %p")
            comid += 1
            tickets["completed"].append(selected_request)   
            tickets["pending"].pop(index)
            save_tickets()  # Save pending list after removal
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
            tickets["canceled"].append(selected_request)
            tickets["pending"].pop(index)
            save_tickets()  # Save pending list after removal
            print("\n\n" + " " * 30 + "+----------------------------------+")
            print(" " * 30 + "| Ticket cancelled successfully!   |")
            print(" " * 30 + "+----------------------------------+")
            time.sleep(3)
            break
        else:
            print("Invalid input! Please type [y] or [n].")
            continue
def compute_rate(index):
    service_rate = 0
    paid_amount = 0

    print("\n" * 3)
    print(" " * 30 + "+------------------------------------+")
    print(" " * 30 + f"| Enter rate of service for ID# {index + 1}    |")
    print(" " * 30 + "| > ", end="")

    while True:
        try:
            service_rate = int(input())
            break
        except ValueError:
            print("\n" + " " * 30 + "+------------------------------------+")
            print(" " * 30 + "| Invalid input! Please enter a      |")
            print(" " * 30 + "| number:                            |")
            print(" " * 30 + "| > ", end="")

    tickets["pending"][index].rate = service_rate

    while True:
        print("\n" + " " * 30 + "+----------------------------------+")
        print(" " * 30 + "| Enter Tendered Amount:           |")
        print(" " * 30 + "| > ", end="")

        try:
            paid_amount = int(input())
        except ValueError:
            print("\n" + " " * 30 + "+----------------------------------+")
            print(" " * 30 + "| Invalid input! Please enter a    |")
            print(" " * 30 + "| number:                          |")
            continue

        change_amount = paid_amount - service_rate

        if change_amount >= 0:
            tickets["pending"][index].date = get_current_datetime("%m-%d-%Y")
            tickets["pending"][index].time = get_current_datetime("%I:%M %p")

            print("\n" + " " * 30 + "+----------------------------------+")
            print(" " * 30 + f"| Change amount: PHP {change_amount:<13} |")
            print(" " * 30 + "+----------------------------------+")
            time.sleep(3)
            receipt(index, change_amount, paid_amount)
            return
        else:
            print("\n" + " " * 30 + "+--------------------------------------------+")
            print(" " * 30 + "|            Insufficient payment.           |")
            print(" " * 30 + f"| Additional amount of PHP {-change_amount:<3} is required.  |")
            print(" " * 30 + "+--------------------------------------------+")
            time.sleep(2)

def receipt(index, change, paid):
    os.system("cls" if os.name == "nt" else "clear")
    print("\n" * 3)
    print(" " * 30 + "=================================================")
    print(" " * 30 + "-------------------------------------------------")
    print("\n" + " " * 30 + f"ID# {index + 1}\t\t\tStatus: {tickets["pending"][index].status}")
    print("\n" + " " * 30 + "-------------------------------------------------")
    print("\n" + " " * 30 + f"Customer Name: {tickets["pending"][index].cname}")
    print(" " * 30 + f"Brand & Model: {tickets["pending"][index].brand} {tickets["pending"][index].model}")
    print(" " * 30 + f"Issue: {tickets["pending"][index].issue}")
    print("\n" + " " * 30 + "-------------------------------------------------")
    print("\n" + " " * 30 + f"Rate of Service: {tickets["pending"][index].rate}")
    print(" " * 30 + f"Tendered Amount: {paid}")
    print(" " * 30 + f"Change: {change}")
    print("\n" + " " * 30 + "-------------------------------------------------")
    print("\n" + " " * 30 + f"\t\t {tickets["pending"][index].date} {tickets["pending"][index].time}")
    print(" " * 30 + "\t\tThank you, Come Again!")
    print("\n" + " " * 30 + "=================================================")
    print("\n\n" + " " * 30 + "+-------------------------------------+")
    print(" " * 30 + "|       Press Enter to proceed:       |")
    print(" " * 30 + "+-------------------------------------+")
    input()

def view_transaction_history():
    os.system("cls" if os.name == "nt" else "clear")
    """Display all completed and canceled requests in a formatted table."""

    # Combine completed and canceled tickets into one list
    history = tickets["completed"] + tickets["canceled"]

    if not history:
        print("\n" + " " * 40 + "+-------------------------------------+")
        print(" " * 40 + "|  No Transaction History to display! |")
        print(" " * 40 + "+-------------------------------------+")
        input(" " * 40 + "Press Enter to return to the main menu...")
        return

    # Table header
    print("\n" + "+" + "-" * 5 + "+" + "-" * 22 + "+" + "-" * 15 + "+" + "-" * 15 + "+" + "-" * 15 + "+"
          + "-" * 20 + "+" + "-" * 32 + "+" + "-" * 12 + "+" + "-" * 10 + "+" + "-" * 12 + "+")
    print("| " + f"{'ID':<3}" + " | " + f"{'Customer Name':<20}" + " | " + f"{'Contact No.':<13}" + " | "
          + f"{'Device Type':<13}" + " | " + f"{'Brand':<13}" + " | " + f"{'Model':<18}" + " | "
          + f"{'Issue':<30}" + " | " + f"{'Priority':<10}" + " | " + f"{'Status':<8}" + " | " + f"{'Rate':<10}" + " |")
    print("+" + "-" * 5 + "+" + "-" * 22 + "+" + "-" * 15 + "+" + "-" * 15 + "+" + "-" * 15 + "+"
          + "-" * 20 + "+" + "-" * 32 + "+" + "-" * 12 + "+" + "-" * 10 + "+" + "-" * 12 + "+")

    # Table rows
    for idx, req in enumerate(history):
        print("| " + f"{idx + 1:<3}" + " | " + f"{req.cname:<20}" + " | " + f"{req.cnum:<13}" + " | "
              + f"{req.dtype:<13}" + " | " + f"{req.brand:<13}" + " | " + f"{req.model:<18}" + " | "
              + f"{req.issue:<30}" + " | " + f"{req.priority:<10}" + " | " + f"{req.status:<8}" + " | "
              + f"{req.rate:<10}" + " |")
        print("+" + "-" * 5 + "+" + "-" * 22 + "+" + "-" * 15 + "+" + "-" * 15 + "+" + "-" * 15 + "+"
              + "-" * 20 + "+" + "-" * 32 + "+" + "-" * 12 + "+" + "-" * 10 + "+" + "-" * 12 + "+")

    input("\nPress Enter to return to the main menu...")

def date_today():
    """Count the number of pending requests for today."""
    return len([req for req in tickets["pending"] if req.date == datetime.now().strftime("%Y-%m-%d")])

def major_counter():
    """Count the number of major priority requests."""
    return len([req for req in tickets["pending"] if req.priority == "Major"])

def minor_counter():
    """Count the number of minor priority requests."""
    return len([req for req in tickets["pending"] if req.priority == "Minor"])


def main_menu():
    date_counter = date_today()
    major = major_counter()
    minor = minor_counter()
    ongoing = len(tickets["pending"])
    global id_counter

    while True:
        os.system("cls" if os.name == "nt" else "clear")
        print("\n" * 4)
        print(" " * 20 + "+----------------------------------+" + "   " + "+----------------------------------+")
        print(" " * 20 + "|    Total No. of Major Request:   |" + "   " + "|    Total No. of Minor Request:   |")
        print(" " * 20 + f"|                {major:<18}|" + "   " + f"|                {minor:<18}|")
        print(" " * 20 + "+----------------------------------+" + "   " + "+----------------------------------+")
        print("\n")
        print(" " * 20 + "+----------------------------------+" + "   " + "+----------------------------------+")
        print(" " * 20 + "|   Total No. of Pending Request:  |" + "   " + "|   No. of Pending Request Today:  |")
        print(" " * 20 + f"|                {ongoing:<18}|" + "   " + f"|                {date_counter:<18}|")
        print(" " * 20 + "+----------------------------------+" + "   " + "+----------------------------------+")
        print("\n" + " " * 40 + "+----------------------------------+")
        print(" " * 40 + "|            WELCOME               |")
        print(" " * 40 + "+----------------------------------+")
        print(" " * 40 + "| Please select an option:         |")
        print(" " * 40 + "|                                  |")
        print(" " * 40 + "| 1. Create a New Ticket           |")
        print(" " * 40 + "| 2. View All Ongoing Requests     |")
        print(" " * 40 + "| 3. Update Ticket                 |")
        print(" " * 40 + "| 4. Payment & Request History     |")
        print(" " * 40 + "| 5. Exit                          |")
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
        elif choice == "5":
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
    load_tickets()
    main_menu()