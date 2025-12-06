import os
from copy import deepcopy

from sklearn.tree import DecisionTreeClassifier

os.environ['OPENBLAS_NUM_THREADS'] = '1'

# from dataset_script import dataset
dataset = []

if __name__ == '__main__':
    percent = int(int(input()) / 100 * len(dataset))
    criteria = input()
    max_n_leaves = int(input())

    train_data = dataset[:percent]
    test_data = dataset[percent:]

    train_x = [row[:-1] for row in train_data]
    train_y = [row[-1] for row in train_data]

    test_x = [row[:-1] for row in test_data]
    test_y = [row[-1] for row in test_data]

    tree = DecisionTreeClassifier(
        criterion=criteria,
        max_leaf_nodes=max_n_leaves,
        random_state=0
    )

    tree.fit(train_x, train_y)
    score = tree.score(test_x, test_y)
    print(f"Tochnost so originalniot klasifikator: {score}")

    predictions_dict = {}
    for c in ['Perch', 'Roach', 'Bream']:
        tree.fit(train_x, [1 if y == c else 0 for y in train_y])
        predictions = tree.predict(test_x)
        predictions_dict[c] = predictions

    count = 0
    for i, y in enumerate(test_y):
        good = True
        for c in ['Perch', 'Roach', 'Bream']:
            if y == c and predictions_dict[c][i] == 1: continue
            elif y != c and predictions_dict[c][i] == 0: continue
            good = False
            break
        if good:
            count += 1

    print(f"Tochnost so kolekcija od klasifikatori: {count / len(test_y)}")



