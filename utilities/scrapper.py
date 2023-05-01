import time
import requests
import pathlib
import concurrent.futures
from selenium import webdriver
from selenium.webdriver.common.by import By

folder = 'audios/mp3'

def fetch_audios(url):
    audios = []
    
    options = webdriver.ChromeOptions()
    options.add_argument("--headless")
    
    driver = webdriver.Chrome(options=options)
    driver.get(url)

    last_height = driver.execute_script("return document.body.scrollHeight")
    
    print("Scrolling...")

    while True:
        driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
        
        time.sleep(0.5)
        
        new_height = driver.execute_script("return document.body.scrollHeight")
        
        if new_height == last_height:
            break
        
        last_height = new_height

    audio_elements = driver.find_elements(By.TAG_NAME, "audio")
    
    for i, audio_element in enumerate(audio_elements):
        audios.append(audio_element.get_attribute("src"))
        
    driver.quit()
    
    print(f"Found {len(audios)} audios")
    
    return audios

def download_audios(url):
    if url.endswith(".mp3"):
        mp3_content = requests.get(url).content
        filename = url.split("/")[-1]
                
        with open(f"{folder}/{filename}", "wb") as f:
            f.write(mp3_content)
            print(f"Saved {filename}")

if __name__ == "__main__":
    urls = fetch_audios("https://www.wikiaves.com.br/midias.php?tm=s&t=s&s=11327")
    
    pathlib.Path(folder).mkdir(parents=True, exist_ok=True)
    
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        executor.map(download_audios, urls)