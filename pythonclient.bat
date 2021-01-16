cd python
python -m venv venv
CALL venv/Scripts/activate.bat
pip install -r ../requirements.txt
python -m grpc_tools.protoc -I../proto --python_out=. --grpc_python_out=. ../proto/*.proto