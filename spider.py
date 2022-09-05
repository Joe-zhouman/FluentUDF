import os
import requests
from lxml import etree


class MeiziSpider:
    def __init__(self):
        '''初始化'''
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36'
        }

    def create_directory(self, path):
        '''创建文件夹'''
        try:
            os.mkdir(path)
        except Exception as e:
            print(e)

    def get_response(self, url, headers=None):
        '''获取网页响应内容'''
        response = requests.get(url, headers=headers)
        return response.text

    def etree_response(self, response):
        '''将response转为可进行xpath的response'''
        response = etree.HTML(response)
        return response

    def download_picture(self, headers, path, url):
        '''下载图片'''
        img_content = requests.get(url, headers=headers).content
        with open(path, 'wb+') as f:
            f.write(img_content)

    def judge_file_exists(self, path):
        '''判断文件是否存在'''
        try:
            f = open(path)
            f.close()
            return True
        except Exception as e:
            return False

    def crawl_picture_url(self, img_name, url):
        '''抓取套图内图片url'''
        print('正在爬取：{}'.format(img_name))
        headers = self.headers
        headers['Referer'] = url
        # 计数,用于构造图片名称
        count = 1
        # 创建套图文件夹
        self.create_directory(img_name)
        # 获取图片地址并下载
        response = self.get_response(url, headers=headers)
        response = self.etree_response(response)
        img_url = response.xpath('//div[@class="main-image"]/p/a/img/@src')
        while True:  # 下载图片
            # 构造图片名
            file_name = img_name + '/' + str(count) + '.jpg'
            # 判断图片是否存在
            if self.judge_file_exists(file_name) == False:
                self.download_picture(
                    headers=headers, path=file_name, url=img_url[0])
            count += 1
            # 获取下一页并下载
            next_page_url = response.xpath('//a[./span/text()="下一页»"]/@href')
            if next_page_url:
                # 获取图片地址并下载
                response = self.get_response(next_page_url[0], headers=headers)
                response = self.etree_response(response)
                img_url = response.xpath(
                    '//div[@class="main-image"]/p/a/img/@src')
            else:
                break
        print('爬取完成：{}'.format(img_name))

    def crawl_page_image_urls(self, url, classify_name):
        '''爬取url内所有套图信息
        参数：
        url：url地址
        name：分类名称(用于构造保存路径)
        '''
        response = self.get_response(url, headers=self.headers)
        response = self.etree_response(response)
        content = response.xpath('//ul[@id="pins"]//li')
        for con in content:
            # 获取套图名称以及地址
            name = con.xpath('./a/img/@alt')[0]
            # 合成路径
            href = con.xpath('./a/@href')[0]
            # 抓取并下载
            self.crawl_picture_url(classify_name + '/' + name, href)

    def crawl_jiepai_zipai(self, url, classify_name):
        '''抓取街拍、自拍图片'''
        # 获取页面内容
        response = self.get_response(url, headers=self.headers)
        response = self.etree_response(response)
        headers = self.headers
        headers['Referer'] = url
        # 获取页面内所有图片地址
        content = response.xpath(
            '//div[@id="comments"]/ul//li//img/@data-original')
        # 循环下载
        for url in content:
            self.download_picture(
                headers=headers, path=classify_name+'/'+url[-12:], url=url)

    def get_classify_info(self, classify_name, url):
        '''获取分类信息'''
        print(classify_name, url)
        # 获取总页数
        response = self.get_response(url, headers=self.headers)
        response = self.etree_response(response)
        if classify_name in ['自拍', '街拍']:
            page_num = response.xpath('//span[@aria-current="page"]/text()')[0]
        else:
            page_num = response.xpath('//a[@class="page-numbers"]/text()')[-1]

        # 选择爬取的页面范围
        while True:
            numbers = input(
                '该分类共有{}页，请选择要爬取的范围:(示例:1-11 注：0退出):\n请输入:'.format(page_num))
            if numbers == '0':
                return False
            numbers = numbers.split('-')
            try:
                start_number = int(numbers[0])
                end_number = int(numbers[1])
                if 1 <= start_number <= int(page_num) and 1 <= end_number <= int(page_num):
                    break
                else:
                    print('输入范围有误，请重新输入！')
                    continue
            except Exception as e:
                print(e)
        # 根据分类创建文件夹
        self.create_directory(classify_name)
        # 抓取范围页面
        print('抓取范围{}-{}'.format(start_number, end_number))
        # 街拍和自拍与其它分类结构不同
        for i in range(start_number, end_number+1):
            if classify_name in ['自拍', '街拍']:
                crawl_url = url + 'comment-page-{}/'.format(i)
                self.crawl_jiepai_zipai(crawl_url, classify_name)
                pass
            else:
                crawl_url = url + 'page/{}/'.format(i)
                print(crawl_url)
                self.crawl_page_image_urls(crawl_url, classify_name)
        print('抓取完成')

    def run(self):
        '''爬取妹子图    四个分类：性感、日本、台湾、清纯
        1.获取分类下所有页面套图url地址
        2.获取套图内所有图片并下载
        '''
        urls_dict = {'性感': 'https://www.mzitu.com/xinggan/',
                     '日本': 'https://www.mzitu.com/japan/',
                     '台湾': 'https://www.mzitu.com/taiwan/',
                     '清纯': 'https://www.mzitu.com/mm/',
                     '自拍': 'https://www.mzitu.com/zipai/',
                     '街拍': 'https://www.mzitu.com/jiepai/'
                     }
        # 选择爬取的分类
        while True:
            choice = input(
                '请输入要爬取的分类:\n1.性感\t2.日本\t3.台湾\t4.清纯\t5.自拍\t6.街拍\t0.退出\n请输入:')
            if choice == '0':
                break
            elif choice in ['1', '2', '3', '4', '5', '6']:
                # 分类与地址
                classify = {'1': '性感', '2': '日本', '3': '台湾',
                            '4': '清纯', '5': '自拍', '6': '街拍'}[choice]
                url = urls_dict[classify]
                self.get_classify_info(classify, url)
            else:
                print('请输入正确内容！')


if __name__ == '__main__':
    meizi = MeiziSpider()
    meizi.run()
