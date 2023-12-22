# Last Light - Technical Documentation

## Table of Contents
- [Introduction](#introduction)
- [Component-Based Architecture](#component-based-architecture)
- [Physics](#physics)
- [AI and Pathfinding](#ai-and-pathfinding)
- [Audio](#audio)
- [User Interface](#user-interface)
- [Memory Management](#memory-management)
- [Libraries](#libraries)
- [Issues](#issues)

## Introduction
Last Light is a top-down shooter game built with C++ and SFML. The game was built as a final project for the C++ Game Dev module.
The game was built with the Entity-Component-System architecture in mind, and uses the Box2D physics engine for collision detection and resolution.
The game features a wave-based enemy spawning system, a simple AI system, and a basic UI system. Built by [Darren](https://github.com/D-Sills) and [Ged](https://github.com/Ged-J).


## Component-Based Architecture
- Utilizes a flexible system where entities (like player, zombies) are composed of various components.
- Promotes reusability and ease of entity management.
- Components are designed to be modular and independent of each other.
- Component examples: Sprite, Stats, Controller, Collider, etc.
- Robust entity management system that allows for easy creation, deletion, and retrieval of entities.
- Entities are stored in a vector and are iterated through to update and render.
- 'Prefab' system allows for easy creation of entities with pre-defined components. E.g, Zombie, Player, HUD, etc.

## Physics
- Uses Box2D physics engine to handle collision detection and resolution.
- Uses custom contact listener to handle collision events, tried to recreate the collision filtering system similar to Unity.

## AI and Pathfinding
- Uses A* pathfinding algorithm to find the shortest path to the player.
- Enemies spawn in waves and move towards the player.
- Enemies will attack the player if they are within a certain range.

## Audio
- Uses SFML audio module to play sound effects and music. OpenAL.
- Uses custom audio manager to handle audio events. Singleton.
- Audio manager is responsible for loading and unloading audio files, playing audio, and stopping audio.
- Audio manager loads audio files into a map and stores them in memory on startup to be played on demand.
- Supports random playback of similar named sounds, e.g, pistol_1, pistol_2, pistol_3, etc.

## User Interface
- Uses the component-based architecture to create UI elements.
- UI elements are composed of various components such as text, sprite, and button.
- Button supports callbacks set via lambda functions.

## Memory Management
- Uses smart pointers to manage memory across the application.
- Object pools are used to manage the creation and deletion of entities, e.g, bullets and zombies. Fully generic and can be used for any type of object.
- Most creation and deletion of components and entities are handled by the entity manager unique to each scene.

## Libraries
- SFML
- Box2D
- Custom ECM
- Custom level loader
- Custom audio manager
- Custom CSV parser

## Issues
- Box2D collision filtering system led to a lot of issues with memory management, constant crashes we could not fix.
- General time constraints and burnout led to a lot of issues with the project. If box2d and object pooling weren't used, the project would have been much easier to complete.
- Many features are present in some capacity but are not fully implemented, e.g, pickups, upgrades, etc.