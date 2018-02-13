# Imports the Google Cloud client library
from google.cloud import pubsub_v1

project_id = 'pubsub-195103'

menu = "\n\n1 - create a topic\n2 - subscribe to a topic\n3 - unsubscribe from a topic\n4 - publish a message\n5 - quit\n> "

publisher = None
subscriber = None

def join(pid):
    global publisher
    global subscriber
    publisher = pubsub_v1.PublisherClient()
    subscriber = pubsub_v1.SubscriberClient()

    print("\nJoined Server {}\n".format(pid))


def create_topic(pid, topic_name):
    topic_path = publisher.topic_path(pid, topic_name)
    topic = publisher.create_topic(topic_path)

    print('Topic created: {}'.format(topic))


def subscribe(pid, subscription_name):
    subscription_path = subscriber.topic_path(pid, subscription_name)

    def callback(message):
        print('Received message: {}'.format(message))
        message.ack()

    subscriber.subscribe(subscription_path, callback=callback)
    print('Listening for messages on {}'.format(subscription_path))


def unsubscribe(pid, subscription_name):
    subscription_path = subscriber.subscription_path(pid, subscription_name)
    subscriber.delete_subscription(subscription_path)

    print('Subscription deleted: {}'.format(subscription_path))


def publish(pid, topic_name, message):
    topic_path = publisher.topic_path(pid, topic_name)

    message = message.encode('utf-8')
    publisher.publish(topic_path, data=message)

    print('Published Message.')


def main():

    print("Welcome to Panther Pub Sub\n")
    join(project_id)

    while(True):
        choice = int(input(menu))

        if choice == 1: # Create a topic
            topic = input("What's the topic?\n>")
            create_topic(project_id, topic)
        elif choice == 2: # Subscribe to a topic
            topic = input("What's the topic?\n>")
            subscribe(project_id, topic)
        elif choice == 3: # Unsubscribe from a topic 
            topic = input("What's the topic?\n>")
            unsubscribe(project_id, topic)
        elif choice == 4: # Publish a message to a topic
            topic = input("What's the topic?\n>")
            message = input("What's the message?\n>")
            publish(project_id, topic, message)
        elif choice == 5: # Quit
            print("Quitting...\n")
            break
        else:
            print("Quitting...\n")
            break

if __name__ == '__main__':
    main()
