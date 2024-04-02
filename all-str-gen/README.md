# All Strings Generator (all-atr-gen)
npm package that offer vibrant toolbox for crafting captivating strings, Numbers, unique hashes and passphrase sentences

### Here is what you can do
- Create Random String: Create your own string mix by matching uppercase & lowercase letters, numbers, and symbols to build custom strings of any length. Need a short, strong password? A wacky username?, unique keys? You got it
- Passphrase: Generate super secured security sentence passphrases in just a pass the word count and magic will hapen. No more struggling to invent unique passwords for all your accounts!
- hashing: Transform any piece of text into a special, scrambled code. Perfect for hiding secret messages or keeping your data safe

## Installation
Enjoy the magics by running
```bash
npm install all-str-gen
```

---

## Usage

### string Generator
Use `stringGenerator()` to generate random usernames, passwords, keys, etc with the count you want.
- The method takes 5 arguments (count, uppercase, lowercase, number, symbols)
- Use true to accept the character to be inluded to your result
- Use false to deny character to not be included to your result
- The count is for how long yor string will be

```bash
const allstrgen = require('all-str-gen')

# Syntax (weave your strings with these options)
const string = allstrgen.stringGenerator(count, uppercase, lowercase, number, symbols)

# Create yours
const string = allstrgen.stringGenerator(8, true, true, false, true)
# This creates a 8-character string with a dazzling mix of uppercase, lowercase, numbers, and symbols
```

---

### Passphrase Generator
Use `generatePassphrase()` to generate passphrase with any word count you want
- The method expect only single argument (count)

```bash
const allstrgen = require('all-str-gen')

# Syntax (summon powerful phrases)
const passPhrase = allstrgen.generatePassphrase(count)

# Generate a mystical passphrase (example)
const passPhrase = allstrgen.generatePassphrase(5)
# This creates a 5-word passphrase, perfect for unlocking forgotten treasures.
```

---

### Hash generator
Use `generateHash()` to make a powerfull hash

```bash
const allstrgen = require('all-str-gen')

# Syntax (transform data into a cryptic code)
const hash = allstrgen.generateHash(input)

#  Encode a secret message (example)
const hash = allstrgen.generateHash('my string')
# This creates a unique hash to safeguard your string
```

---

You have an issue? Let us know [Report an issue](https://github.com/matayo-ayo/all-str-gen/issues)