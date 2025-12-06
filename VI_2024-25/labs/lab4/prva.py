import os

from sklearn.model_selection import train_test_split

os.environ['OPENBLAS_NUM_THREADS'] = '1'
# from submission_script import *
# from dataset_script import dataset
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import OrdinalEncoder

from zad1_dataset import dataset

# Ova e primerok od podatochnoto mnozestvo, za treniranje/evaluacija koristete ja
# importiranata promenliva dataset
dataset_sample = [['C', 'S', 'O', '1', '2', '1', '1', '2', '1', '2', '0'],
                  ['D', 'S', 'O', '1', '3', '1', '1', '2', '1', '2', '0'],
                  ['C', 'S', 'O', '1', '3', '1', '1', '2', '1', '1', '0'],
                  ['D', 'S', 'O', '1', '3', '1', '1', '2', '1', '2', '0'],
                  ['D', 'A', 'O', '1', '3', '1', '1', '2', '1', '2', '0']]

if __name__ == '__main__':
    # Vashiot kod tuka
    x = int(input()) / 100
    encoder = OrdinalEncoder()
    encoder.fit([row[:-1] for row in dataset])

    train_data = dataset[int(len(dataset) * (1.0 - x)):]
    test_data = dataset[:int(len(dataset) * (1.0 - x))]

    train_X = [row[:-1] for row in train_data]
    train_Y = [row[-1] for row in train_data]
    train_X = encoder.transform(train_X)

    test_X = [row[:-1] for row in test_data]
    test_Y = [row[-1] for row in test_data]

    test_X = encoder.transform(test_X)

    criterion = input()

    classifier = DecisionTreeClassifier(criterion=criterion, random_state=0)
    classifier.fit(train_X, train_Y)

    print(f'Depth: {classifier.get_depth()}')
    print(f'Number of leaves: {classifier.get_n_leaves()}')
    print(f'Accuracy {classifier.score(test_X, test_Y)}')

    features = classifier.feature_importances_
    max_i = max(list(features))
    min_i = min(list(features))

    for i, feature in enumerate(features):
        if feature == max_i:
            print(f'Most important feature: {i}')
        if feature == min_i:
            print(f'Least important feature: {i}')

    # Na kraj potrebno e da napravite submit na podatochnoto mnozestvo,
    # klasifikatorot i encoderot so povik na slednite funkcii

    # submit na trenirachkoto mnozestvo
    # submit_train_data(train_X, train_Y)

    # submit na testirachkoto mnozestvo
    # submit_test_data(test_X, test_Y)

    # submit na klasifikatorot
    # submit_classifier(classifier)

    # submit na encoderot
    # submit_encoder(encoder)
