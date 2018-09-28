import math

# Calculate the classification with the highest frequency in a dataset
def majority(data, attributes, target):
    freq = {}
    max = 0;
    major = ''
    for example in data:
        value = example[target]
        if value in freq:
            freq[value] += 1;
        else:
            freq[value] = 1
    for key in freq:
        if freq[key] > max:
            max = freq[key]
            major = key
    return major


# Calculate the entropy of a dataset for a given attribute
def entropy(data, target):
    nvalues = len(data)
    freq = {}
    entropy_value = 0.0
    for entry in data:
        attr = entry[target]
        if attr in freq:
            freq[attr] += 1.0
        else:
            freq[attr] = 1.0
    for attr in freq:
        entropy_value += (freq[attr] / nvalues) * math.log2(freq[attr] / nvalues)
    return -entropy_value

# Calculate the information gain from splitting the tree on a chosen attribute
def gain(data, attribute, target):
    freq = {}
    base_entropy = entropy(data, target)
    subset_entropy = 0.0
    for entry in data:
        value = entry[attribute]
        if value in freq:
            freq[value] += 1.0
        else:
            freq[value] = 1.0
    for value in freq:
        prob_value = freq[value] / sum(freq.values())
        data_subset = [ex for ex in data if ex[attribute] == value]
        subset_entropy += prob_value * entropy(data_subset, target)
    return base_entropy - subset_entropy


# Choose the best attribute to split the dataset on
def choose(data, attributes, target):
    best = attributes[0]
    maxGain = 0
    for attr in attributes:
        if attr != target:
            g = gain(data, attr, target)
            if g > maxGain:
                maxGain = g;
                best = attr
    return best

# Split the dataset on an attribute when its value is equal to val
def split(data, attribute, val):
    examples = []
    for ex in data:
        if (ex[attribute] == val):
            newEx = ex.copy()
            del newEx[attribute]
            examples.append(newEx)
    return examples


# Group continous valous in varying bins to reduce the size of the tree
def discretize(data, attribute, target, size):
    # Sort the data set by this attribute
    data.sort(key=lambda ex: ex[attribute])
    group = []
    groups = []
    last = None
    for i in range(len(data)):
        entry = data[i]
        if entry[attribute] not in group:
            group.append(entry[attribute])
        if len(group) == size:
            if last == None:
                groups.append((group[0], group[-1]))
            else:
                groups.append((last, group[-1]))
            last = group[-1]
            group = []
    if group != []:
        groups.append((last, group[-1]))
    group = groups[0]
    groups[0] = (group[0], group[1], lambda x,lo,hi: x >= lo and x <= hi, '[{},{}]'.format(group[0], group[1]))
    for i in range(1,len(groups)):
        group = groups[i]
        groups[i] = (group[0], group[1], lambda x,lo,hi: x > lo and x <= hi, ']{},{}]'.format(group[0], group[1]))
    # this works so lets not touch it anymore
    for entry in data:
        val = entry[attribute]
        first = groups[0]
        if val >= first[0] and val <= first[1]:
            entry[attribute] = '[{},{}]'.format(first[0], first[1])
        for group in groups[1:]:
            if val > group[0] and val <= group[1]:
                entry[attribute] = ']{},{}]'.format(group[0], group[1])
    return groups


# Convert a value into its assigned bin
def discrete(value, bins):
    for bin in bins:
        if bin[2](value, bin[0], bin[1]):
            return bin[3]
