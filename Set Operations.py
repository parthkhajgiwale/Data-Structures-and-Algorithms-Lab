class Set:
    def __init__(self):
        self.elements = []

    def add(self, new_element):
        if new_element not in self.elements:
            self.elements.append(new_element)

    def remove(self, element):
        if element in self.elements:
            self.elements.remove(element)

    def contains(self, element):
        return element in self.elements

    def size(self):
        return len(self.elements)

    def iterator(self):
        return iter(self.elements)

    def intersection(self, other_set):
        intersection_set = Set()
        for element in self.elements:
            if element in other_set.elements:
                intersection_set.add(element)
        return intersection_set

    def union(self, other_set):
        union_set = Set()
        for element in self.elements:
            union_set.add(element)
        for element in other_set.elements:
            union_set.add(element)
        return union_set

    def difference(self, other_set):
        difference_set = Set()
        for element in self.elements:
            if element not in other_set.elements:
                difference_set.add(element)
        return difference_set

    def subset(self, other_set):
        for element in self.elements:
            if element not in other_set.elements:
                return False
        return True


# Menu driven code
def menu():
    set_1 = Set()
    set_2 = Set()
    while True:
        print("==== Set Operations Menu ====")
        print("1. Add element to Set 1")
        print("2. Remove element from Set 1")
        print("3. Check if element is in Set 1")
        print("4. Get size of Set 1")
        print("5. Perform intersection of Set 1 and Set 2")
        print("6. Perform union of Set 1 and Set 2")
        print("7. Get difference between Set 1 and Set 2")
        print("8. Check if Set 1 is a subset of Set 2")
        print("9. Exit")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            element = input("Enter the element to add: ")
            set_1.add(element)
            print("Element added to Set 1.")
        elif choice == 2:
            element = input("Enter the element to remove: ")
            set_1.remove(element)
            print("Element removed from Set 1.")
        elif choice == 3:
            element = input("Enter the element to check: ")
            if set_1.contains(element):
                print("Element is in Set 1.")
            else:
                print("Element is not in Set 1.")
        elif choice == 4:
            print("Size of Set 1 is:", set_1.size())
        elif choice == 5:
            intersection = set_1.intersection(set_2)
            print("Intersection of Set 1 and Set 2:", intersection.elements)
        elif choice == 6:
            union = set_1.union(set_2)
            print("Union of Set 1 and Set 2:", union.elements)
        elif choice == 7:
            difference = set_1.difference(set_2)
            print("Difference between Set 1 and Set 2:", difference.elements)
        elif choice == 8:
            if set_1.subset(set_2):
                print("Set 1 is a subset of Set 2.")
            else:
                print("Set 1 is not a subset of Set 2.")
        elif choice == 9:
            print("Exiting the program...")
            break
        else:
            print("Invalid choice. Please try again.")


# Run the menu
menu()
