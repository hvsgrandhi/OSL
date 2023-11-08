#!/bin/bash

# Initialize an empty address book file
address_book_file="address_book.txt"

# Check if the address book file exists; if not, create one
if [ ! -e "$address_book_file" ]; then
  touch "$address_book_file"
fi

while true; do
  echo "Address Book Menu:"
  echo "a) Create address book"
  echo "b) View address book"
  echo "c) Insert a record"
  echo "d) Delete a record"
  echo "e) Modify a record"
  echo "f) Exit"
  read -p "Enter your choice: " choice

  case "$choice" in
    a)
      echo "Creating a new address book."
      rm "$address_book_file" # Clear the existing address book if it exists
      touch "$address_book_file"
      ;;
    b)
      echo "Viewing address book:"
      cat "$address_book_file"
      ;;
    c)
      read -p "Enter name: " name
      read -p "Enter address: " address
      echo "Name: $name, Address: $address" >> "$address_book_file"
      echo "Record inserted successfully."
      ;;
    d)
      read -p "Enter name to delete: " name
      sed -i "/Name: $name, Address: /d" "$address_book_file"
      echo "Record deleted successfully."
      ;;
    e)
      read -p "Enter name to modify: " name
      read -p "Enter new address: " new_address
      sed -i "s/Name: $name, Address: .*/Name: $name, Address: $new_address/g" "$address_book_file"
      echo "Record modified successfully."
      ;;
    f)
      echo "Exiting the address book program."
      exit 0
      ;;
    *)
      echo "Invalid choice. Please choose a valid option (a, b, c, d, e, or f)."
      ;;
  esac
done
