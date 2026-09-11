# Installing Unreal Engine Module from GitHub

This guide explains how to install and use the custom GASImplementation module for Unreal Engine from a GitHub repository.

## Prerequisites

- Unreal Engine 5.7.1 installed
- Git installed on your system
- Your Unreal Engine project set up

## Installation Steps

### Method 1: Manual Installation

1. **Navigate to your project's Plugins directory**
   ```bash
   cd {YourProject}/Plugins
   ```
   
   If the `Plugins` folder doesn't exist, create it in your project root directory.


2. **Clone the repository**
   ```bash
   git clone https://github.com/jessetmia/GASImplementation.git
   ```
   or with SSH: 
   ```bash
   git clone git@github.com:jessetmia/GASImplementation.git
   ```

3. **Regenerate project files**
   - Right-click on your `.uproject` file
   - Select "Generate Visual Studio project files" or "Switch Unreal Engine version"
   - This will update your project to recognize the new plugin


4. **Open the project**
   - Open your `.uproject` file in Unreal Engine
   - If prompted about missing or incompatible modules, choose to rebuild them


5. **Enable the plugin**
   - In the Unreal Engine Editor, go to **Edit > Plugins**
   - Search for GASImplementation
   - Check the **Enabled** checkbox
   - Restart the editor when prompted


6. Open {YourProject}.Build.cs and update `PublicDependencyModuleNames.AddRange(new string[] { ..., "GASImplementation" });` to include the plugin

### Method 2: Git Submodule (Recommended for Version Control)

1. **Add the module as a submodule**
   ```bash
   git submodule add https://github.com/jessetmia/GASImplementation.git Plugins/GASImplementation
   ```

2. **Initialize and update the submodule**
   ```bash
   git submodule update --init --recursive
   ```

3. **Follow steps 3-6 from Method 1**

### Method 3: Download as ZIP

1. **Download the repository**
   - Go to the GitHub repository page
   - Click the green **Code** button
   - Select **Download ZIP**

2. **Extract to Plugins folder**
   - Extract the ZIP file
   - Copy the extracted folder to `{YourProject}/Plugins/`

3. **Follow steps 3-6 from Method 1**

## Verifying Installation

1. Open your project in Unreal Engine
2. Go to **Edit > Plugins**
3. Confirm the plugin appears in the list and is enabled
4. Check the Output Log for any errors related to the plugin

## Using the plugin

This plugin contains all the classes needed to get a basic GAS Implementation for a character/NPCs
Currently, it contains the following classes:
- BaseGameMode
- BaseCharacter
- BasePlayerCharacter
- BaseCharacterMovementComponent
- BasePlayerController
- BasePlayerState
- BaseAbilitySystemComponent
- BaseAttributeSet

As well as the following Abilities: 
- BaseAbility 
- CrouchAbility
- JumpAbility
- SprintAbility

With the following Effects:
- **InitializeBaseAttributes** - Sets the Base Attributes for the character
- **SprintEffect** - Both the sprint movementspeed bonus and stam drain effects
- **ExhaustedEffect** - When the character's stamina reaches 0, this effect will prevent stam regen and sprint.

For an example of GAS AttributeSets, we have included the following attributes:
- Stamina
- MaxStamina
- MovementSpeed

Base values can be modified by updating the InitializeBaseAttributes Effect.

The following Blueprints are included:
- BP_PlayerCharacter - This uses Manny as the mesh
- BP_PlayerController
- BP_TestGameMode

Input Actions are included for the following:
- Jump
- Sprint
- Crouch
- Look
- Move

## How to play

All classes should be extendedable for Blueprints, but default values should be set to allow for immediate play by setting
Gamemode to BP_TestGameMode in editor. This has been tested with first and 3rd person default projects in UE5.

No animations are included in this plugin. The BP_PlayerCharacter uses the manny mesh, and unarmed ABP.


