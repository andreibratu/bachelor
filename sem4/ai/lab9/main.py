import tensorflow as tf
from tensorflow.keras import models


def get_model() -> models.Sequential:
    # Based on LeNet architecture
    nn = models.Sequential()
    nn.add(tf.keras.layers.Conv2D(32, [3, 3], activation='relu', input_shape=(28, 28, 1)))
    nn.add(tf.keras.layers.Conv2D(64, [3, 3], activation='relu'))
    nn.add(tf.keras.layers.MaxPooling2D(pool_size=(2, 2)))
    nn.add(tf.keras.layers.Dropout(0.25))
    nn.add(tf.keras.layers.Flatten())
    nn.add(tf.keras.layers.Dense(128, activation='relu'))
    nn.add(tf.keras.layers.Dropout(0.5))
    nn.add(tf.keras.layers.Dense(10))
    """
    Per https://www.tensorflow.org/api_docs/python/tf/keras/losses/SparseCategoricalCrossentropy
    SparseCategoricalCrossEntropy allows us to skip the one-hot encoding step that would be 
    required if the final layer used softmax activation - if the one-hot encoding approach was
    used, CategoricalCrossEntropy would have done the trick. 
    """
    nn.compile(
        loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
        optimizer=tf.keras.optimizers.Adam(),
        metrics=['accuracy']
    )
    return nn


if __name__ == '__main__':
    (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
    # Rescale the images from [0,255] to the [0.0, 1.0] range.
    x_train, x_test = x_train / 255.0, x_test / 255.0
    # TF will complain if the received data is not 4-dimensional
    x_train = x_train.reshape(-1, 28, 28, 1)
    x_test = x_test.reshape(-1, 28, 28, 1)
    # Model training and results
    model = get_model()
    model.fit(x_train,
              y_train,
              batch_size=128,
              epochs=5,
              verbose=1,
              validation_data=(x_test, y_test))
    cnn_results = model.evaluate(x_test, y_test)
    # Final scores: loss: 0.0346 - accuracy: 0.9888
