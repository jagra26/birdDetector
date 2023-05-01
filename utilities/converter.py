import os
import pathlib
import concurrent.futures
from pydub import AudioSegment

def mp3_to_wav(file):
    if file.endswith(".mp3"):
        src = file
        dst = f"audios/wav/{src.split('/')[-1].replace('.mp3', '.wav')}"
        
        try:
            sound = AudioSegment.from_file(src, format="mp3")
            sound.export(dst, format="wav")
            
            print(f"Converted {file} to {dst}")
        except:
            return


if __name__ == "__main__":
    folder = 'audios/mp3'
    dst_folder = 'audios/wav'
    files = []

    pathlib.Path(dst_folder).mkdir(parents=True, exist_ok=True)

    for file in os.listdir(folder):
        files.append(f"{folder}/{file}")
    
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        executor.map(mp3_to_wav, files)