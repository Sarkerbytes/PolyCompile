# ─────────────────────────────────────────────
#  Stage 1: Build the C++ PolyCompile binary
# ─────────────────────────────────────────────
FROM node:20-bookworm-slim AS builder

# Install build tools (g++, flex, bison, make)
RUN apt-get update && apt-get install -y \
    g++ \
    flex \
    bison \
    make \
    && rm -rf /var/lib/apt/lists/*

# Copy the full project
WORKDIR /app
COPY . .

# Step 1: Generate flex/bison parser files for all 3 languages
RUN make flex-c flex-cpp flex-java

# Step 2: Build the C++ compiler binary (verbose for debugging)
RUN make all VERBOSE=1 || (echo "=== MAKE FAILED ===" && cat /app/compiler/c/frontend/Frontend_C.cpp | head -5 && exit 2)

# Install Node.js dependencies
RUN cd server && npm install --omit=dev

# ─────────────────────────────────────────────
#  Stage 2: Runtime image
# ─────────────────────────────────────────────
FROM node:20-bookworm-slim

# Install only the runtime C++ library (needed to run the compiled binary)
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy compiled binary + output dir + server from builder
COPY --from=builder /app/polycompile ./polycompile
COPY --from=builder /app/output ./output
COPY --from=builder /app/server ./server

# Make the binary executable
RUN chmod +x ./polycompile

# Create temp directory for uploaded source files
RUN mkdir -p ./server/temp

# Expose the port (Render sets PORT env var automatically)
EXPOSE 3000

# Start the Node.js server
CMD ["node", "server/server.js"]
