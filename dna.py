import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py databases/[filename.csv] sequences/[filename.text]")
        sys.exit(1)

    # TODO: Read database file into a variable (rows[])
    # set variable rows as a list, every element is a dictionary
    rows = []
    # first line default recognized as fieldnames
    # row is dictionary that starts after fieldnames: {"fieldname": Key, "fieldname": Value, "fieldname": Value, ...}
    # reader是函数csv.DictReader(file)的返还对象，数据类型是迭代器
    # rows是一个list，每个元素是一个dictionary，list可以随机访问，迭代器只能顺序访问
    with open(sys.argv[1]) as csvFile:
        csv_reader = csv.DictReader(csvFile)
        for row in csv_reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    # Open the file
    with open(sys.argv[2], "r") as textFile:
    # Read the contents of the file into a variable
        sequence = textFile.read()

    # TODO: Find longest match of each STR in DNA sequence
    if sys.argv[1].endswith("small.csv"):
        subsequence = ["AGATC", "AATG", "TATC"]
    elif sys.argv[1].endswith("large.csv"):
        subsequence = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
    else:
        print("Can not find database")
        sys.exit(1)

    # Create a list with undefined space for elements, this setting could be better used with append function
    target_STR = []
    for i in range(len(subsequence)):
        frequency = longest_match(sequence, subsequence[i])
        target_STR.append(str(frequency))

    # TODO: Check database for matching profiles
    for person in rows:
        dict_values = list(person.values())[1:]
        if dict_values == target_STR:
            print(person["name"])
            break
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
