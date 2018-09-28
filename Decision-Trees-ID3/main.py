from settings import *
from dataIO import *
from id3util import *

# Get all the possible values for an attribute on a dataset
def getValues(data, attribute):
    values = set()
    for entry in data:
        values.add(entry[attribute])
    return values


# Build a decision tree based on the ID3 algorithm
def makeTree(data, parent_data, attributes, target):
    data = data.copy()
    # attributes = [key for key in attribute_data.keys()]
    # If the dataset is empty return the value with the highest frequency
    # in the parent dataset
    if not data:
        major = majority(parent_data, attributes, target)
        return {'class':major, 'count':0}
    # If only the target attribute is left in the attribute list
    # return the value with with highest frequency in the current dataset
    if len(attributes) == 1:
        major = majority(data, attributes, target)
        return {'class':major, 'count':1}
    # If all examples have the same classification then return that
    # classification
    classList = [ex[target] for ex in data]
    if classList and classList.count(classList[0]) == len(classList):
        return {'class':classList[0], 'count':len(classList)}
    # Choose the best attribute to split the tree on.
    # This node will have a branch for each possible value this attribute can
    # take. Then build a new tree for each branch, considering only examples
    # where the chosen attribute has the branch value, and removing this
    # attribute from the list
    best = choose(data, attributes, target)
    tree = {best:{}}
    for value in getValues(parent_data, best):
        examples = split(data, best, value)
        # attr_data = attribute_data.copy()
        # del attr_data[best]
        attr_data = attributes.copy()
        attr_data.remove(best)
        tree[best][value] = makeTree(examples, parent_data, attr_data, target)
    return tree


# Classify examples read from file
def answer(file, tree, binmap):
    with open(file, newline = '') as csvfile:
        read = csv.DictReader(csvfile, delimiter = ',')
        for row in read:
            classification = classify(row, tree, binmap)
            print(row['ID']+':', classification)


# Classify an example recursively
def classify(example, tree, binmap):
    if 'class' in tree:
        return tree['class']
    for attr in tree:
        value = example[attr]
        if attr in binmap:
            value = discrete(value, binmap[attr])
        if attr in example:
            return classify(example, tree[attr][value], binmap)


def main():
    problem = input("Which dataset to load?\n restaurant | weather | iris\n")
    problem = problems[problem]

    examples, attributes, attribute_data = init_data(problem['file'])
    target = problem['target']

    binmap = {}
    for attr in problem['continuous']:
        binmap[attr] = discretize(examples, attr, target, problem['size'])

    tree = makeTree(examples, examples, attributes, target)

    file = open(problem['outfile'], 'w')
    writeTree(file, tree, "")

    testfile = input("Enter file to test tree with\n")
    if testfile == 'default':
        testfile = problem['testfile']
    answer(testfile, tree, binmap)


main()

# def splitContinuous():
#     prev = data[0][target]
#     bestSet = []
#     maxGain = 0
#     for entry in data:
#         if entry[target] != prev:
#             examples = [ x.copy() for x in data]
#             threshold = entry[attribute]
#             for ex in examples:
#                 if ex[attribute] < threshold:
#                     ex[attribute] = '<{}'.format(threshold)
#                 else:
#                     ex[attribute] = '>={}'.format(threshold)
#             g = gain(examples, attribute, target)
#             if g > maxGain:
#                 maxGain = g
#                 bestSet = examples
#         prev = entry[target]
#     return bestSet
