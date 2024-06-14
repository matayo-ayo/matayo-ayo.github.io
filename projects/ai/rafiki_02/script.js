// Array of responses from ChatGPT
const responses = [
    "Subiri kidogo kuna vitu nimesahau 😂!",
    "Aaanh 🤔. Hili swali ni gumu bhana",
    "Bado nipo katika majaribio 😭",
    "Mhhh, nimedondosha miwani 👓",
    "Ukija baadae nitakuwa na jibu 🙈",
    "Leo, kimeumana 😩",
    "Ngoja kwanza niisome simu yako 🗝️"
];

document.addEventListener("DOMContentLoaded", function () {
    displayWelcomeMessage();
});

function displayWelcomeMessage() {
    var randomIndex = Math.floor(Math.random() * responses.length);
    var randomResponse = responses[randomIndex];
    addMessage("ChatGPT", randomResponse);
}

function sendMessage() {
    var messageInput = document.getElementById("message-input");
    var messageText = messageInput.value.trim();

    if (messageText !== "") {
        addMessage("You", messageText);

        // Simulate a reply after a short delay
        setTimeout(function () {
            var randomIndex = Math.floor(Math.random() * responses.length);
            var randomResponse = responses[randomIndex];
            addMessage("ChatGPT", randomResponse);
        }, Math.random() * 1000 + 500); // Random delay between 0.5 to 1.5 seconds

        messageInput.value = "";
    }
}

function addMessage(user, text) {
    var chatBox = document.querySelector(".chat-box");

    var messageContainer = document.createElement("div");
    messageContainer.classList.add("message");

    var messageBody = document.createElement("div");
    messageBody.classList.add("message-body");

    var textElement = document.createElement("div");
    textElement.textContent = text;

    messageBody.appendChild(textElement);
    messageContainer.appendChild(messageBody);

    if (user === "You") {
        messageContainer.classList.add("sent");
    } else {
        messageContainer.classList.add("received");
    }

    chatBox.appendChild(messageContainer);

    // Scroll to bottom
    chatBox.scrollTop = chatBox.scrollHeight;
}

document.addEventListener("DOMContentLoaded", function() {
    // Toggle FAQ section visibility on button click
    var toggleFaqBtn = document.getElementById('toggleFaqBtn');
    var faqSidebar = document.querySelector('.faq-sidebar');
    var faqOverlay = document.querySelector('.faq-overlay');

    toggleFaqBtn.addEventListener('click', function() {
        faqSidebar.classList.toggle('hidden');
        faqOverlay.classList.toggle('hidden');
    });

    // Close sidebar and overlay if overlay is clicked
    faqOverlay.addEventListener('click', function() {
        faqSidebar.classList.add('hidden');
        faqOverlay.classList.add('hidden');
    });
});
