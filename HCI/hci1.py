from tkinter import *
from tkinter import messagebox

# Function to handle login
def handle():
    # Get the email and password from the entry widgets
    ee = e.get()  # e.get() fetches the email entered
    pp = p.get()  # p.get() fetches the password entered
    
    # Check if the credentials are correct
    if ee == "abc@gmail.com" and pp == "abc":
        messagebox.showinfo("Login Success", "Welcome!")
    else:
        messagebox.showerror("Login Error", "Try again")

# Create the main window
root = Tk()
root.title("Login Page")
root.geometry('300x300')  # Window size
root.configure(background='blue')  # Background color

# Add a label for the title
Label(root, text="Login", font=('Arial', 20), bg='black', fg='white').pack(pady=(10, 20))

# Add a label and an entry field for email
Label(root, text="Email").pack(pady=5)
e = Entry(root, width=30)  # Create Entry widget for email
e.pack(pady=5)

# Add a label and an entry field for password
Label(root, text="Password").pack(pady=5)
p = Entry(root, width=30, show='*')  # Create Entry widget for password (masked)
p.pack(pady=5)

# Add a login button and link it to the handle function
Button(root, text="Login", command=handle).pack(pady=5)

# Run the Tkinter event loop
root.mainloop()