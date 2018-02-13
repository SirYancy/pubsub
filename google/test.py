# Imports the Google Cloud client library
from google.cloud import pubsub_v1

# Instantiates a client
publisher = pubsub_v1.PublisherClient()

# The resource path for the new topic contains the project ID
# and the topic name.
topic_path = publisher.topic_path(
    'pubsub-195103', 'my-new-topic')

# Create the topic.
topic = publisher.create_topic(topic_path)

print('Topic created: {}'.format(topic))
