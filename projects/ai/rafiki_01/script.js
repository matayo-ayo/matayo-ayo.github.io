document.getElementById('chat-form').addEventListener('submit', function (event) {
    event.preventDefault();
    const input = document.getElementById('message-input');
    const message = input.value.trim();
    if (message) {
        addMessage('user', message);
        input.value = '';
        // Simulate AI response
        setTimeout(() => {
            addMessage('ai', 'Huu ni mfano wa jibu la AI.');
        }, 1000);
    }
});

function addMessage(sender, text) {
    const messageContainer = document.getElementById('chat-messages');
    const messageElement = document.createElement('div');
    messageElement.className = `flex ${sender === 'user' ? 'justify-end' : 'justify-start'}`;
    messageElement.innerHTML = `
        <div class="${sender === 'user' ? 'bg-blue-500 text-white' : 'bg-gray-200 text-black'} rounded-lg p-3 max-w-xs">
            ${text}
        </div>
    `;
    messageContainer.appendChild(messageElement);
    messageContainer.scrollTop = messageContainer.scrollHeight;
}

document.querySelectorAll('aside button').forEach(button => {
    button.addEventListener('click', function () {
        const question = this.textContent;
        addMessage('user', question);
        setTimeout(() => {
            addMessage('ai', 'Na huu ni mfano wa jibu la swali lako la : ' + question);
        }, 1000);
    });
});