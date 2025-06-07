
-- local.lua (in your project folder or a config folder)


-- Place this in the root of your project (same directory as the `.sln` file)
local M = {}

-- Your solution file (optional, useful for building/debugging references)
M.project_sln = "ClientApp.sln"

-- Path to your executable (relative to the project root)
M.executable = vim.fn.getcwd() .. "\\ClientApp\\bin\\Debug\\net8.0-windows\\ClientApp.exe"

return M

