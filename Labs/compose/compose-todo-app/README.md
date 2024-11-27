# To-Do App

This is a sample to-do application for use in the PXL containers course.

## Tech Stack

The stack represents a combination of a JavaScript-based backend (Node.js with Express), a modern frontend framework (React), database technologies (SQLite and MySQL), and containerization (Docker), making it a comprehensive example for full-stack development and deployment.

The technology stack includes:

- __Node.js__: The backend application is built using Node.js, a JavaScript runtime environment that executes JavaScript code outside a web browser.

- __Express.js__: This is a minimal and flexible Node.js web application framework that provides a robust set of features for web and mobile applications. It is used to create the server and handle HTTP requests.

- __React.js__: The frontend is built using React, a JavaScript library for building user interfaces. It is used to create the interactive UI components for the application.

- __SQLite__: This is a C-language library that implements a small, fast, self-contained, high-reliability, full-featured, SQL database engine. SQLite is used as one of the database options for the application.

- __MySQL__: This is a popular open-source relational database management system. In this application, MySQL is used as an alternative database option to SQLite.

- __Docker__: The application is designed to be containerized using Docker, which allows for isolating the application in containers to simplify deployment and scalability.

- __Bootstrap & Font Awesome__: For styling, the application uses Bootstrap, a front-end framework for developing responsive and mobile-first websites, and Font Awesome for icons.

- __Jest__: This is a JavaScript testing framework used for writing tests for the application.

- __Prettier__ & __ESLint__: These are code formatting and linting tools to ensure code quality and consistency.

## Components

- `package.json`: Defines the Node.js application's dependencies, scripts, and other configuration details.
- `src/index.js`: The main entry point for the Node.js application. It sets up an Express server, initializes database connections, and defines routes for CRUD operations on 'todo' items.
- Persistence Layer (`src/persistence`):
  - `index.js`: Determines whether to use MySQL or SQLite based on the environment configuration.
  - `mysql.js` & `sqlite.js`: Implement database operations for MySQL and SQLite, respectively.
- Routes (`src/routes`): Contains Express route handlers for adding, deleting, retrieving, and updating 'todo' items.
- Frontend (`src/static`):
  - index.html: The main HTML file for the frontend.
  - app.js: A React-based frontend script that interacts with the backend to display and manage 'todo' items.

This application serves as a practical example for Docker users to understand how to containerize a simple web application using Docker.

## Persistence Layer

### Current Implementation in `index.js`

The `index.js` file in the `src/persistence` directory currently checks for the presence of a MySQL configuration in the environment variables. If MySQL-related environment variables are set, it uses MySQL; otherwise, it defaults to SQLite. The relevant code is:

```javascript
if (process.env.MYSQL_HOST) module.exports = require('./mysql');
else module.exports = require('./sqlite');
```

### Adaptations You Might Need

1. **Environment Variables**: Ensure that the environment variables for MySQL (like `MYSQL_HOST`, `MYSQL_USER`, `MYSQL_PASSWORD`, etc.) are correctly set in your deployment environment when you want to use MySQL. If these variables are not set, the application will default to using SQLite.

2. **Database Configuration Files**: The `mysql.js` and `sqlite.js` files contain the specific configurations and initialization code for each database.

By adapting these aspects of the `index.js` file and related configurations, you can control which database the application uses based on your deployment environment or other conditions.