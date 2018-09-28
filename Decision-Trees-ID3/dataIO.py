import csv
from settings import DEBUG

# Read a dataset from a csv file, using Python's csv library
# We omit the ID and classification attributes from the data fed to the
# learning algorith
# This function returns a list of all examples, stored as a dictionary,
# a list of all attributes, and a dictionary mapping attributes to lists of
# their possible values
def init_data(file):
    with open(file, newline = '') as csvfile:
        read = csv.DictReader(csvfile, delimiter = ',')
        attribute_data = {field:set() for field in read.fieldnames[1:-1]}
        example_data = []
        for row in read:
            del row['ID']
            for field in read.fieldnames[1:-1]:
                attribute_data[field].add(row[field])
            example_data.append(row)
    return example_data, read.fieldnames[1:-1], attribute_data

# Write the built tree to file following this format:
#   <attribute1>
#       value1: classification (counter)
#       value2:
#           <attribute2>
#               ...
#       ...
def writeTree(file, tree, indent):
    for attr in tree:
        file.write('{}<{}>\n'.format(indent, attr))
        if DEBUG:
            print('{}<{}>'.format(indent, attr))
        indent += '\t'
        for value in tree[attr]:
            subtree = tree[attr][value]
            if 'class' in subtree:
                file.write('{}{}: {} ({})\n'.format(indent, value, subtree['class'], subtree['count']))
                if DEBUG:
                    print('{}{}: {} ({})'.format(indent, value, subtree['class'], subtree['count']))
            else:
                file.write('{}{}:\n'.format(indent, value))
                if DEBUG:
                    print('{}{}:'.format(indent, value))
                writeTree(file, subtree, indent+'\t')
