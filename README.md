# 🐦 Flappy Bird Clone — Built with C++ & SFML

A lightweight yet extensible Flappy Bird-style game developed in C++ using the SFML library. This project focuses on clean architecture, real-time rendering, and a responsive scoring system — designed as a foundation for deeper game mechanics and player experience enhancements.

## 🧪 How to Run

1. Clone the repository  
2. Make sure SFML is installed  
3. Compile with your preferred compiler (e.g. g++, clang++)  
4. Run the executable and enjoy!


## 🚀 Features

- 🎮 Core gameplay loop with gravity, jump mechanics, and obstacle spawning
- 🧠 Collision detection between bird and pipes
- 🧮 Dynamic scoring system with real-time updates
- 🎨 SFML-based rendering pipeline with smooth frame updates
- 🔊 Sound effect integration (structure ready, implementation pending)
- 🧱 Modular codebase with enum-driven state management and function abstraction

---
## 🧩 Gameplay Logic

- The bird is affected by gravity and responds to spacebar input for jumping.
- Pipes are spawned at intervals and move horizontally across the screen.
- When the bird successfully passes a pipe, the score increments.
- Collision with pipes or ground ends the game.

---

## 📈 Future Enhancements

This project is actively evolving. Planned features include:

- 🪙 Coin collection system  
- 🔊 Sound and visual effects  
- 🌐 Network-based high score sharing  
- 🧠 Difficulty scaling based on score  

---

## 🧠 Developer Notes

This project is built with a focus on **code clarity**, **modular design**, and **learning-by-dissection**. Each component is structured to be easily extendable, making it ideal for developers exploring game architecture in C++.

If you're interested in contributing, feel free to fork the repo and submit a pull request. Feedback and suggestions are always welcome.

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## 🙌 Acknowledgments

Special thanks to the SFML community and open-source contributors who make game development accessible and enjoyable.
